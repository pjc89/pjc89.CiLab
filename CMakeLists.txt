cmake_minimum_required(VERSION 3.25)
project(cilab C)

find_package(ZLIB REQUIRED)

add_executable(cilab main.c)
target_link_libraries(cilab PRIVATE ZLIB::ZLIB)
