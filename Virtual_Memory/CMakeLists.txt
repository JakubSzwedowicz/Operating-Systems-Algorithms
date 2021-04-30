cmake_minimum_required(VERSION 3.16)

set(PROJECT_NAME "Page replacement algorithms")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED on)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wno-missing-braces")

project(${PROJECT_NAME}
        DESCRIPTION "Project simulating page replacement algorithms which are operating on RAM/HDD"
        VERSION 1.0
        LANGUAGES CXX)

add_subdirectory(app)
add_subdirectory(src)