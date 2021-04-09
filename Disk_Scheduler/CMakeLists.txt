cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "Hard drive access algorithms")
set(RESOURCES_DIR ${PROJECT_SOURCE_DIR}/resources)
set(CMAKE_CXX_FLAGS "-g -Wall -Werror -Wno-missing-braces")
set(CMAKE_CXX_STANDARD 17)


option(test "Build all tests." ON)

project(${PROJECT_NAME}
        DESCRIPTION "Project tests different algorithms that manage hard drive access"
        VERSION 1.0
        LANGUAGES CXX)

add_subdirectory(app)
add_subdirectory(src)
add_subdirectory(tests)

file(GLOB MY_FILES ${RESOURCES_DIR}/*.txt)
file(COPY ${MY_FILES} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/app)