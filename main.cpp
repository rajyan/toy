#include <iostream>
#include <set>
#include <cassert>

#include "BloomFilter.h"
#include "../library/src/RandNum.cpp"
#include "../library/src/timer.cpp"

std::string random_string(const std::size_t& max_len) {
    RandNum ran;
    std::size_t size = ran(1, max_len);
    std::string res(size, 0);
    std::generate(res.begin(), res.end(), [&ran]() { return 'a' + ran(std::numeric_limits<long long>::max()) % 26; });
    return res;
}

int main() {

    constexpr std::size_t len_max = 30;
    constexpr std::size_t vec_size = 100;
    constexpr std::size_t test_size = 1000000;
    constexpr std::size_t hash_num = 3;
    constexpr std::size_t table_size = 500;

    std::vector<std::string> vec(vec_size);
    for (std::size_t i = 0; i < vec_size; i++) {
        vec[i] = random_string(len_max);
    }

    std::set<std::string> st;
    BloomFilter bf(hash_num, table_size);
    RandNum ran;

    std::size_t fp_count = 0;
    std::size_t contains_count = 0;
    for (int i = 0; i < test_size; i++) {
        std::size_t index = ran(0, vec_size - 1);
        if (ran(0, 1)) {
            st.emplace(vec[index / 2]);
            bf.add(vec[index / 2]);
        }
        else {
            contains_count++;
            bool st_exists = st.find(vec[index]) != st.end();
            bool bf_exists = bf.contains(vec[index]);

            // no false negative
            assert(!(st_exists && !bf_exists));

            if (!st_exists && bf_exists) {
                std::cout << "false positive with " << vec[index] << '\n';
                fp_count++;
            }
        }
    }

    std::cout << "false positive rate: " << 1.0 * fp_count / contains_count << '\n';

    return 0;
}
