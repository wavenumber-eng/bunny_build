cmake_minimum_required(VERSION 3.10)

project(bunny_build)

set(APP_SOURCE
    ${CMAKE_SOURCE_DIR}/../../src/bunny_build.c
    ${CMAKE_SOURCE_DIR}/main.c
)


add_executable(bunny_build  ${APP_SOURCE})

target_compile_definitions(bunny_build PUBLIC)

target_include_directories(bunny_build PUBLIC "${CMAKE_SOURCE_DIR}/../../src")
     

