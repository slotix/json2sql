cmake_minimum_required(VERSION 3.9)
project(JSON2SQL_CONVERTER DESCRIPTION "JSON to SQL converter. Website: https://dbconvert.com")
set(CMAKE_CXX_STANDARD 11)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_CXX_FLAGS "-Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

enable_testing()

add_subdirectory(test)
add_subdirectory(json2sql)
add_subdirectory(example/1)
add_subdirectory(example/2)
add_subdirectory(example/3)
