#pragma once
#include "GECore/Core.h"
#include "GEUtils/Queue.h"

class simple_thread_pool
{
public:
	explicit simple_thread_pool(uint32_t threads = std::thread::hardware_concurrency())
	{
		if (!threads)
			throw std::invalid_argument("Invalid thread count!");

		auto worker = [this]() {
			while (true)
			{
				Proc f;
				if (!m_queue.pop(f))
					break;
				f();
			}
		};

		for (auto i = 0; i < threads; ++i)
			m_threads.emplace_back(worker);
	}

	~simple_thread_pool()
	{
		m_queue.done();
		for (auto &thread : m_threads)
			thread.join();
	}

	template <typename F, typename... Args>
	void enqueue_work(F &&f, Args &&... args)
	{
		m_queue.push([p = std::forward<F>(f), t = std::make_tuple(std::forward<Args>(args)...)]() { std::apply(p, t); });
	}

	template <typename F, typename... Args>
	[[nodiscard]] auto enqueue_task(F &&f, Args &&... args) -> std::future<std::invoke_result_t<F, Args...>>
	{
		using task_return_type = std::invoke_result_t<F, Args...>;
		using task_type = std::packaged_task<task_return_type()>;

		auto task = std::make_shared<task_type>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		auto result = task->get_future();

		m_queue.push([task]() { (*task)(); });

		return result;
	}

private:
	using Proc = std::function<void(void)>;
	using Queue = blocking_queue<Proc>;
	Queue m_queue;

	using Threads = std::vector<std::thread>;
	Threads m_threads;
};

class thread_pool
{
public:
	explicit thread_pool(uint32_t threads = std::thread::hardware_concurrency())
		: m_queues(threads), m_count(threads)
	{
		if (!threads)
			throw std::invalid_argument("Invalid thread count!");

		auto worker = [this](auto i) {
			while (true)
			{
				Proc f;
				for (auto n = 0; n < m_count * K; ++n)
					if (m_queues[(i + n) % m_count].try_pop(f))
						break;
				if (!f && !m_queues[i].pop(f))
					break;
				f();
			}
		};

		for (auto i = 0; i < threads; ++i)
			m_threads.emplace_back(worker, i);
	}

	~thread_pool()
	{
		for (auto &queue : m_queues)
			queue.done();
		for (auto &thread : m_threads)
			thread.join();
	}

	template <typename F, typename... Args>
	void enqueue_work(F &&f, Args &&... args)
	{
		auto work = [p = std::forward<F>(f), t = std::make_tuple(std::forward<Args>(args)...)]() { std::apply(p, t); };
		auto i = m_index++;

		for (auto n = 0; n < m_count * K; ++n)
			if (m_queues[(i + n) % m_count].try_push(work))
				return;

		m_queues[i % m_count].push(std::move(work));
	}

	template <typename F, typename... Args>
	[[nodiscard]] auto enqueue_task(F &&f, Args &&... args) -> std::future<std::invoke_result_t<F, Args...>>
	{
		using task_return_type = std::invoke_result_t<F, Args...>;
		using task_type = std::packaged_task<task_return_type()>;

		auto task = std::make_shared<task_type>(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
		auto work = [task]() { (*task)(); };
		auto result = task->get_future();
		auto i = m_index++;

		for (auto n = 0; n < m_count * K; ++n)
			if (m_queues[(i + n) % m_count].try_push(work))
				return result;

		m_queues[i % m_count].push(std::move(work));

		return result;
	}

private:
	using Proc = std::function<void(void)>;
	using Queue = blocking_queue<Proc>;
	using Queues = std::vector<Queue>;
	Queues m_queues;

	using Threads = std::vector<std::thread>;
	Threads m_threads;

	const uint32_t m_count;
	std::atomic_uint m_index = 0;

	inline static const uint32_t K = 2;
};

class ThreadPool
{
public:
	ThreadPool(size_t);
	template <class F, class... Args>
	auto enqueue(F &&f, Args &&... args)
		-> std::future<typename std::result_of<F(Args...)>::type>;
	~ThreadPool();

private:
	// need to keep track of threads so we can join them
	std::vector<std::thread> workers;
	// the task queue
	std::queue<std::function<void()>> tasks;

	// synchronization
	std::mutex queue_mutex;
	std::condition_variable condition;
	bool stop = false;
};

inline ThreadPool::ThreadPool(size_t threads)
{
	for (size_t i = 0; i < threads; ++i)
	{
		workers.emplace_back([this] {
			while (1)
			{
				std::function<void()> task;
				{
					std::unique_lock<std::mutex> lock(this->queue_mutex);
					this->condition.wait(lock,
										 [this] { return this->stop || !this->tasks.empty(); });
					if (this->stop && this->tasks.empty())
						return;
					task = std::move(this->tasks.front());
					this->tasks.pop();
				}

				task();
			}
		});
	}
}

// the destructor joins all threads
inline ThreadPool::~ThreadPool()
{
	{
		std::unique_lock<std::mutex> lock(queue_mutex);
		stop = true;
	}
	condition.notify_all();
	for (std::thread &worker : workers)
		worker.join();
}

// add new work item to the pool
template <class F, class... Args>
auto ThreadPool::enqueue(F &&f, Args &&... args)
	-> std::future<typename std::result_of<F(Args...)>::type>
{
	using return_type = typename std::result_of<F(Args...)>::type;

	auto task = std::make_shared<std::packaged_task<return_type()>>(
		std::bind(std::forward<F>(f), std::forward<Args>(args)...));

	std::future<return_type> res = task->get_future();
	{
		std::unique_lock<std::mutex> lock(queue_mutex);

		// don't allow enqueueing after stopping the pool
		if (stop)
			throw std::runtime_error("enqueue on stopped ThreadPool");

		tasks.emplace([task]() { (*task)(); });
	}
	condition.notify_one();
	return res;
}
