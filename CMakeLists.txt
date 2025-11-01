cmake_minimum_required(VERSION 3.22)
project(units_cli C)               # <<< проект точно C
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Библиотека с логикой
add_library(units STATIC src/convert.c)
target_include_directories(units PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Исполняемый файл
add_executable(units_cli src/main.c)
target_link_libraries(units_cli PRIVATE units)
# Явно добавим include-путь и к исполняемому таргету, чтобы IDE не путалась
target_include_directories(units_cli PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)

# Тесты
enable_testing()
add_executable(test_convert tests/test_convert.c)
target_link_libraries(test_convert PRIVATE units)
add_test(NAME convert_tests COMMAND test_convert)
