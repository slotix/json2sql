project(json2sql)

#file(GLOB RAPIDJSON_HEADERS
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson/*.h
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson/internal/*.h
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson/error/*.h
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson/msinttypes/*.h)
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/third-party/rapidjson)


set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON )
add_library(json2sql SHARED
        include/field.hpp
        src/field.cpp
        include/config.hpp
        )
#target_include_directories(json2sql PUBLIC
#        ${PROJECT_SOURCE_DIR}/include
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson/internal
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson/error
#        ${PROJECT_SOURCE_DIR}/third-party/rapidjson/msinttypes
#)
#target_include_directories(json2sql PUBLIC ${PROJECT_SOURCE_DIR}/third-party/rapidjson)
