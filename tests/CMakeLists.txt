include(FetchContent)
FetchContent_Declare(Catch2 GIT_REPOSITORY https://github.com/catchorg/Catch2 GIT_TAG v2.13.10)
FetchContent_MakeAvailable(Catch2)

add_executable(unit_tests test.cpp)
target_link_libraries(unit_tests PUBLIC calculator Catch2)