cmake_minimum_required(VERSION 3.22)

# Проект на C (НЕ C++)
project(units_cli C)

# Стандарт и варнинги
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# ----- Библиотека с логикой конвертаций -----
# Файлы: include/convert.h, src/convert.c
add_library(units STATIC src/convert.c)
target_include_directories(units PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ----- Исполняемый файл -----
# Файл: src/main.c
add_executable(units_cli src/main.c)
target_link_libraries(units_cli PRIVATE units)
target_include_directories(units_cli PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ----- Тесты -----
enable_testing()
# Файл: tests/test_convert.c (содержит свой main)
add_executable(test_convert tests/test_convert.c
        tests/test_more.c)
target_link_libraries(test_convert PRIVATE units)
add_test(NAME convert_tests COMMAND test_convert)
# Тесты
enable_testing()

add_executable(test_convert tests/test_convert.c
        tests/test_more.c)
target_link_libraries(test_convert PRIVATE units)
add_test(NAME convert_tests COMMAND test_convert)

add_executable(test_more tests/test_more.c
        tests/test_more.c)         # <— новый тест
target_link_libraries(test_more PRIVATE units)
add_test(NAME more_tests COMMAND test_more)

# CLI tests (через CTest)
add_test(NAME cli_len_cm_to_in
        COMMAND units_cli len 10 cm in)
set_tests_properties(cli_len_cm_to_in PROPERTIES
        PASS_REGULAR_EXPRESSION "3\\.9370078")

add_test(NAME cli_temp_c_to_f
        COMMAND units_cli temp 25 C F)
set_tests_properties(cli_temp_c_to_f PROPERTIES
        PASS_REGULAR_EXPRESSION "^77(\\.0+)?$")
