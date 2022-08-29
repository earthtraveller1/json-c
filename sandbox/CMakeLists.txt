add_executable("sandbox")

target_link_libraries("sandbox" "json-c")

target_include_directories("sandbox" PRIVATE "${CMAKE_SOURCE_DIR}/src")

add_subdirectory("src")