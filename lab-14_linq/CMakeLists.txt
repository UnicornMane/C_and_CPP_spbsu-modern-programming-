cmake_minimum_required(VERSION 3.22.1)
project(lab-14_linq)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)
include_directories(include)
include_directories(src)

add_executable(lab-14_linq_minimal_smoke_test
        include/linq.hpp
        src/minimal_smoke_test.cpp)

add_executable(lab-14_linq_smoke_test
        include/linq.hpp
        src/smoke_test.cpp)

add_executable(lab-14_linq
        include/linq.hpp
        src/test.cpp)
