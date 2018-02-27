project(json2sql)

include_directories( ${json2sql_SOURCE_DIR}/include)


set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library(json2sql SHARED
        include/config.hpp
        include/field.hpp
        include/record.hpp
        include/table.hpp
        src/field.cpp
        src/record.cpp include/hash_table.hpp include/enum_table.hpp include/record_set.hpp src/record_set.cpp include/enum_record_set.hpp src/enum_record_set.cpp include/hash_record_set.hpp src/hash_record_set.cpp)
target_include_directories(json2sql PUBLIC
        ${PROJECT_SOURCE_DIR}/third-party/rapidjson
)

