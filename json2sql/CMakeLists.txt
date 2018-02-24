project(json2sql)

include_directories(${PROJECT_SOURCE_DIR}/include)
#include_directories(${PROJECT_SOURCE_DIR}/third-party/rapidjson)

set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library(json2sql SHARED
        include/field.hpp
        src/field.cpp
        include/config.hpp
        )
target_include_directories(json2sql PUBLIC
        ${PROJECT_SOURCE_DIR}/third-party/rapidjson
)

