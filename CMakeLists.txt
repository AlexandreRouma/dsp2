cmake_minimum_required(VERSION 3.13)
project(dsp)

file(GLOB_RECURSE SRC "src/*.cpp" "dsp/*.cpp")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE "dsp/")

target_compile_options(${PROJECT_NAME} PRIVATE /std:c++20)