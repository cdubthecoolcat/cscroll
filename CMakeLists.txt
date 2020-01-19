cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER "clang-9")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(cscroll)

include_directories(include)
aux_source_directory(src SOURCE_FILES)
add_executable(cscroll ${SOURCE_FILES})
target_link_libraries(cscroll bsd m)
