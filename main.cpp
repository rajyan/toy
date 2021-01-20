#include <iostream>
#include "BloomFilter.h"

int main() {

    BloomFilter bf(10, 32);

    std::string test1 = "abcdef";
    std::string test2 = "abcdefg";
    bf.add(test1);
    
    std::cout << bf.contains(test1) << '\n';
    std::cout << bf.contains(test2) << '\n';

    bf.add(test2);

    std::cout << bf.contains(test2) << '\n';

    return 0;
}
