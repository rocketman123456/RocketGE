#pragma once
#include <vector>
#include <algorithm>
#include <iterator>

// 这种数据帧一般以某种特定数据序列表示开始（例如0xa5,0x5a)和结束(0xb5, 0x5b)，
// 起始标记间的数据为帧有效数据。

template <typename T>
class FrameParser
{
public:
    FrameParser(const std::vector<T> &headTag, const std::vector<T> &tailTag, const bool discardTag = true)
        : frameHeadTag(headTag), frameTailTag(tailTag), discardFrameTag{discardTag}
    {
    }

    bool isDiscardFrameTag() const
    {
        return discardFrameTag;
    }

    template <class It>
    void append(It f, It l)
    {
        buffer.insert(buffer.end(), f, l);
    }
    void append(const std::vector<T> &data)
    {
        buffer.insert(buffer.end(), data.cbegin(), data.cend());
    }

    void parse(std::vector<std::vector<T>> &frames)
    {
        auto it_head{buffer.cbegin()};
        for (auto it_tail{std::search(it_head, buffer.cend(), frameTailTag.cbegin(), frameTailTag.cend())};
             it_tail != buffer.cend(); it_tail = std::search(it_head, buffer.cend(), frameTailTag.cbegin(), frameTailTag.cend()))
        {
            it_head = std::search(it_head, it_tail, frameHeadTag.cbegin(), frameHeadTag.cend());
            if (it_head != it_tail)
            {
                frames.emplace_back(isDiscardFrameTag() ? it_head + frameHeadTag.size() : it_head, isDiscardFrameTag() ? it_tail : it_tail + frameTailTag.size());
            }
            it_head = std::next(it_tail, frameTailTag.size());
        }

        tempBuffer.insert(tempBuffer.end(), it_head, buffer.cend());
        std::swap(buffer, tempBuffer);
        tempBuffer.clear();
    }

private:
    bool discardFrameTag{true};
    const std::vector<T> frameHeadTag;
    const std::vector<T> frameTailTag;
    std::vector<T> buffer;
    std::vector<T> tempBuffer;
};
