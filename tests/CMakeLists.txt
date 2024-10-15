cmake_minimum_required(VERSION 3.8)

set(APPNAME "kd_tests")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wempty-body -Wredundant-move -Wno-error=deprecated-declarations -Wno-writable-strings -Wimplicit-fallthrough")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wempty-body -Wno-error=deprecated-declarations -Wno-writable-strings -Wimplicit-fallthrough")

file(GLOB_RECURSE SRC_LIST
    "*.cpp"
    "*.hpp"
    ${PROJECT_SOURCE_DIR}/src/*.cpp
    ${PROJECT_SOURCE_DIR}/src/*.hpp)

add_executable(${APPNAME} ${SRC_LIST})

enable_testing()

add_subdirectory(${PROJECT_SOURCE_DIR}/tests/googletest)
target_link_libraries(
    ${APPNAME}
    GTest::gtest_main
    pqxx
    fmt
)
include(GoogleTest)
gtest_discover_tests(${APPNAME})

include_directories(${PROJECT_SOURCE_DIR}/src/contrib/pqxx/include)
include_directories(${PROJECT_SOURCE_DIR}/src/contrib/fmt/include)
include_directories(${PROJECT_SOURCE_DIR}/src/)
