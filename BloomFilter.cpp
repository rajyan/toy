//
// Created by rajyan on 2021/01/20.
//

#include "BloomFilter.h"
#include "../library/src/fnv1a.cpp"

uint64_t Hash(const std::string& key) {
    return fnv1a_64(key);
}

std::vector<uint32_t> BloomFilter::calcIndices(const std::string& key) const {
    uint64_t hash = Hash(key);
    uint32_t upper = hash >> 32;
    uint32_t lower = hash;
    std::vector<uint32_t> res(m_hashNum);
    for (int i = 0; i < m_hashNum; i++) {
        res[i] = (upper + lower * i) % m_size;
    }
    return res;
}

void BloomFilter::add(const std::string& key) {
    auto indices = calcIndices(key);
    for (const auto& i: indices) {
        m_bits[i] = true;
    }
}

bool BloomFilter::contains(const std::string& key) const {
    auto indices = calcIndices(key);
    return std::all_of(indices.begin(), indices.end(), [this](auto i) { return m_bits[i]; });
}
