#include_directory()

add_executable(a.out main.cpp)
#target_link_libraries(a.out PUBLIC )
target_include_directories(a.out PUBLIC "${CMAKE_BINARY_DIR}/config/include/")