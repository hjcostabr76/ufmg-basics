#cmake_minimum_required(VERSION 3.12)
cmake_minimum_required(VERSION 3.9.1)
project(TrashRecycling)

set(CMAKE_CXX_STANDARD 14)
set(APP_TARGET "trash-recycling")

file(GLOB_RECURSE SRC_CODE_FILES
    MAIN_CPP code/src/main.cpp
    GLOB_CPP_PATTERNS code/src/**/*.cpp
    GLOB_H_PATTERNS code/header/**/*.h
)

add_executable(${APP_TARGET} ${SRC_CODE_FILES})
target_compile_options(${APP_TARGET} PRIVATE -Wall -Wextra)