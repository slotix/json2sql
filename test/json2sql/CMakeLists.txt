project(test_json2sql)
file(GLOB TEST_FILES *.cpp)
include_directories(${CMAKE_SOURCE_DIR}/json2sql/include)
include_directories(${CMAKE_SOURCE_DIR}/json2sql/third-party/rapidjson)
include_directories(${gtest_SOURCE_DIR})

add_executable(test_json2sql ${TEST_FILES})
target_link_libraries(test_json2sql libgtest json2sql)

add_test(NAME json2sql_test
        COMMAND json2sql_test)
