#include <iostream>
#include <set>
#include <cassert>

#include "BloomFilter.h"
#include "../library/src/Random.hpp"
#include "../library/src/Timer.hpp"

int main() {

    constexpr std::size_t key_max = 30;
    constexpr std::size_t init_size = 500;
    constexpr std::size_t test_size = 1000000;
    constexpr std::size_t table_size = 10000;
    constexpr std::size_t hash_num = (std::size_t)(0.7 * table_size / init_size + 0.5);

    Random ran;
    vector<std::string> keys(init_size);
    generate(keys.begin(), keys.end(), [&]() { return ran.random_string(key_max); });

    // STL set
    std::set<std::string> st;
    // Bloom Filter
    BloomFilter bf(hash_num, table_size);    for (const auto &key : keys) {
        st.emplace(key);
        bf.add(key);
    }

    // assert BloomFilter contains the initial values
    for (const auto &key : st) {
        assert(bf.contains(key));
    }

    std::size_t fp_count = 0;
    for (int i = 0; i < test_size; i++) {

        std::string key = ran.random_string(key_max);
        bool st_exists = st.find(key) != st.end();
        bool bf_exists = bf.contains(key);

        // no false negative
        assert(!(st_exists && !bf_exists));

        if (!st_exists && bf_exists) {
            std::cout << "false positive with " << key << '\n';
            fp_count++;
        }
    }

    std::cout << "false positive rate: " << 1.0 * fp_count / test_size << '\n';

    return 0;
}
