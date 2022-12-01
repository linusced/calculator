add_subdirectory(calculator)

add_executable(calc main.cpp)
target_link_libraries(calc PUBLIC calculator)