cmake_minimum_required(VERSION 3.22)
project(units_cli C)
set(CMAKE_C_STANDARD 11)

# строгие варнинги
if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(units src/convert.c)
target_include_directories(units PUBLIC include)

add_executable(units_cli src/main.c)
target_link_libraries(units_cli units)

# Тесты
enable_testing()
add_executable(test_convert tests/test_convert.c)
target_link_libraries(test_convert units)
add_test(NAME convert_tests COMMAND test_convert)
