cmake_minimum_required(VERSION 3.10)
set(CMAKE_C_COMPILER "clang")
set(CMAKE_C_FLAGS "-O3 -Wall")
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

project(cscroll)

include_directories(include)
aux_source_directory(src SOURCE_FILES)
add_executable(cscroll ${SOURCE_FILES})
target_link_libraries(cscroll)
