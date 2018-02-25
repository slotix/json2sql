project(test_json2sql)
include_directories(${CMAKE_SOURCE_DIR}/json2sql/include)
include_directories(${CMAKE_SOURCE_DIR}/json2sql/third-party/rapidjson)
include_directories("${source_dir}/googletest/include")

add_executable(json2sql_test
        main.cpp
        field.cpp
        record.cpp
        hash_table.cpp
        enum_table.cpp
        table.cpp
        )
target_link_libraries(json2sql_test libgtest json2sql)

add_test(NAME json2sql_test
        COMMAND json2sql_test)
