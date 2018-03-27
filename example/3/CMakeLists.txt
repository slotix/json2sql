project(example3)

include_directories(${CMAKE_SOURCE_DIR}/json2sql/include)

IF (WIN32)
    add_definitions(-DOPEN_MODE="rb")
ELSE()
    add_definitions(-DOPEN_MODE="r")
ENDIF()

add_executable(example3 main.cpp)
add_dependencies(example3 json2sql)
target_link_libraries(example3 json2sql)