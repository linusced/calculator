cmake_minimum_required(VERSION 3.3.2)

project("Calculator" VERSION 0.1.0 LANGUAGES C CXX)

option(UNIT_TESTING "Build unit tests" OFF)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_subdirectory(src)

if (UNIT_TESTING)
    add_subdirectory(tests)
endif()