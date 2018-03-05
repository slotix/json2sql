project(example2)

include_directories(${CMAKE_SOURCE_DIR}/json2sql/include)

IF (WIN32)
    add_definitions(-DOPEN_MODE="rb")
ELSE()
    add_definitions(-DOPEN_MODE="r")
ENDIF()

add_executable(example2 main.cpp)
add_dependencies(example2 json2sql)
target_link_libraries(example2 json2sql)
configure_file(example.json example.json)
