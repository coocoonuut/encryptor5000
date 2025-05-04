cmake_minimum_required(VERSION 3.10)
project(encryptor5000 C)

set(CMAKE_C_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/build)

include_directories(include)

file(GLOB_RECURSE SOURCE_FILES "src/*.c")

add_executable(${PROJECT_NAME} src/main.c ${SOURCE_FILES})