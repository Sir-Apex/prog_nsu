cmake_minimum_required(VERSION 3.5.1)
project(Haffman C)

set(CMAKE_C_STANDARD 99)

set(SRC main.c)

add_executable(${PROJECT_NAME} ${SRC})

