cmake_minimum_required(VERSION 3.16)

project("JSON C")

set(CMAKE_C_STANDARD 17)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

if (WIN32)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin")
else()
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
endif()

if (MSVC)
    add_compile_options("/W4")
    add_compile_definitions("_CRT_SECURE_NO_WARNINGS")
else()
    add_compile_options("-Wall" "-Wpedantic")
endif()

add_library("json-c")

add_subdirectory("src")

add_subdirectory("sandbox")