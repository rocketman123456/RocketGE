#pragma once
#include "GECore/Core.h"

struct H
{
	std::string s1, s2;
};

inline std::ostream &operator<<(std::ostream &os, const H &h)
{
	os << h.s1 << "," << h.s2;
	return os;
}

namespace std
{
	template <>
	struct hash<H>
	{
		size_t operator()(const H &h) const
		{
			return hash<std::string>{}(h.s1) ^ (hash<std::string>{}(h.s2) << 1);
		}
	};
} // namespace std

template <typename T>
auto hashN(const T &key, std::size_t N) -> std::vector<std::size_t>
{
	std::minstd_rand0 rng(std::hash<T>{}(key));
	std::vector<std::size_t> hashes(N);
	std::generate(std::begin(hashes), std::end(hashes), rng);
	return hashes;
}

template <std::size_t N, typename T>
auto hashNT(const T &key) -> std::array<std::size_t, N>
{
	std::minstd_rand0 rng(std::hash<T>{}(key));
	std::array<std::size_t, N> hashes{};
	std::generate(std::begin(hashes), std::end(hashes), rng);
	return hashes;
}