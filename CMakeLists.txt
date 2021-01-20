cmake_minimum_required(VERSION 3.16)
project(toy)

set(CMAKE_CXX_STANDARD 17)

add_executable(toy main.cpp BloomFilter.cpp BloomFilter.h)