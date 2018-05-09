cmake_minimum_required(VERSION 3.10)
project(PostMachine C)

set(CMAKE_C_STANDARD 11)

add_executable(PostMachine main.c comand.c menu.c run.c tape.c)