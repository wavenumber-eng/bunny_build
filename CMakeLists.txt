cmake_minimum_required(VERSION 3.10)

project(ezbuild)

file(GLOB_RECURSE
     APP_SOURCE
        
        ${CMAKE_SOURCE_DIR}/src/*.c
                  
     )


add_executable(ezbuild  ${APP_SOURCE})

target_compile_definitions(ezbuild PUBLIC  SIMULATOR=1)


target_include_directories(ezbuild PUBLIC "${CMAKE_SOURCE_DIR}/src")
     

