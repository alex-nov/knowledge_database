cmake_minimum_required(VERSION 3.8)

set(APPNAME "knowledge_database")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(TARGET_NAME "knowledge_database")
set(AP_VERSION 0.1.0)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Werror -Wempty-body -Wredundant-move -Wno-error=deprecated-declarations -Wno-writable-strings -Wimplicit-fallthrough -fsanitize=address -fsanitize=undefined")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -Wall -Werror -Wempty-body -Wno-error=deprecated-declarations -Wno-writable-strings -Wimplicit-fallthrough")

project(${APPNAME}
        VERSION ${AP_VERSION}
        DESCRIPTION "String example C++ built with CMake and googletest"
        LANGUAGES CXX)

file(GLOB ALL_SRC
        "main.cpp"
)

add_executable(${APPNAME} ${ALL_SRC})

add_subdirectory(${PROJECT_SOURCE_DIR}/src/contrib/pqxx)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/contrib/fmt)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/contrib/logger)
add_subdirectory(${PROJECT_SOURCE_DIR}/src/knowledge_manager)
add_subdirectory(${PROJECT_SOURCE_DIR}/tests)

target_link_libraries(${APPNAME} logger)
target_link_libraries(${APPNAME} knowledge_manager)
