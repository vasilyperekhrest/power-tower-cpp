cmake_minimum_required(VERSION 3.19)
project(power_tower_cpp)

set(CMAKE_CXX_STANDARD 17)

include_directories("/usr/local/include")
link_directories("/usr/local/lib")

add_executable(power_tower_cpp
        main.cpp)

target_link_libraries(power_tower_cpp
        flint
        gmp
        gmpxx)
