cmake_minimum_required(VERSION 3.9)
project(JSON2SQL_CONVERTER DESCRIPTION "JSON to SQL converter. Website: https://dbconvert.com")
set(CMAKE_CXX_STANDARD 11)

enable_testing()

add_subdirectory(test)
add_subdirectory(json2sql)
add_subdirectory(example/1)
add_subdirectory(example/2)
