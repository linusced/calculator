set(FILES parse.cpp calculate.cpp)

add_library(calculator STATIC ${FILES})
target_include_directories(calculator PUBLIC include/)