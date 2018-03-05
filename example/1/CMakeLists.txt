project(example1)

include_directories(${CMAKE_SOURCE_DIR}/json2sql/include)

add_executable(example1 main.cpp)
add_dependencies(example1 json2sql)
target_link_libraries(example1 json2sql)