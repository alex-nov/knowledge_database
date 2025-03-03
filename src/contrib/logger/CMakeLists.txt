cmake_minimum_required(VERSION 3.8)

set(LIBRARY_NAME "logger")
project(${LIBRARY_NAME})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(AP_VERSION 1.0.0)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wempty-body -Wredundant-move -Wno-error=deprecated-declarations -Wno-writable-strings -Wimplicit-fallthrough")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wempty-body -Wno-error=deprecated-declarations -Wno-writable-strings -Wimplicit-fallthrough")

file(GLOB_RECURSE ALL_SRC
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.c
)

add_library(${LIBRARY_NAME} STATIC ${ALL_SRC})

set(LOGGER_INCLUDE_DIR "${PROJECT_SOURCE_DIR}/src/contrib/logger/include")
target_include_directories(${LIBRARY_NAME} SYSTEM INTERFACE ${LOGGER_INCLUDE_DIR})

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${SOURCE_DIR_HEADER})
