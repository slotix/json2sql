project(test_json2sql)
file(GLOB TEST_FILES *.cpp)
include_directories(${CMAKE_SOURCE_DIR}/json2sql/include)
include_directories(${CMAKE_SOURCE_DIR}/json2sql/third-party/rapidjson)
include_directories(${gtest_SOURCE_DIR})

add_executable(json2sql_test ${TEST_FILES})
target_link_libraries(json2sql_test libgtest json2sql)

add_test(NAME json2sql_test
        COMMAND json2sql_test)
