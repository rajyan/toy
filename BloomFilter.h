//
// Created by rajyan on 2021/01/20.
//

#ifndef TOY_BLOOMFILTER_H
#define TOY_BLOOMFILTER_H

#include <cstdint>
#include <vector>
#include <algorithm>

class BloomFilter {
public:
    BloomFilter(std::size_t hashNum, std::size_t size) : m_hashNum(hashNum), m_size(size), m_bits(size) {}
    void add(std::string& key);
    bool contains(std::string& key) const;

private:
    std::size_t m_hashNum;
    std::size_t m_size;
    std::vector<bool> m_bits;

    std::vector<uint32_t> calcIndices(std::string& key) const;
};

#endif //TOY_BLOOMFILTER_H
