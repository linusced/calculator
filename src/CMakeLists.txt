add_subdirectory(calculator)

add_executable(calc main.cpp)
target_link_libraries(calc PUBLIC calculator)
target_include_directories(calc PUBLIC "${CMAKE_BINARY_DIR}/config/include/")