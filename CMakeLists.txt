cmake_minimum_required(VERSION 3.16)

project("TMake")

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
else()
    add_compile_options("-Wall" "-Wpedantic")
endif()

add_executable("tmake")

add_subdirectory("src")