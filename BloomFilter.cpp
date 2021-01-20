//
// Created by rajyan on 2021/01/20.
//

#include "BloomFilter.h"
#include "../library/src/fnv1a.cpp"

uint64_t Hash(std::string& key) {
    return fnv1a_64(key);
}

std::vector<uint32_t> BloomFilter::calcIndices(std::string& key) const {
    uint64_t hash = Hash(key);
    uint32_t upper = hash >> 32;
    uint32_t lower = hash;
    auto res = std::vector<uint32_t>(m_hashNum);
    for (int i = 0; i < m_hashNum; i++) {
        res[i] = (upper + lower * i) % m_size;
    }
    return res;
}

void BloomFilter::add(std::string& key) {
    auto indices = calcIndices(key);
    for (int i = 0; i < m_hashNum; i++) {
        m_bits[indices[i]] = true;
    }
}

bool BloomFilter::contains(std::string& key) const {
    auto indices = calcIndices(key);
    return std::all_of(indices.begin(), indices.end(), [this](auto i) { return m_bits[i]; });
}
