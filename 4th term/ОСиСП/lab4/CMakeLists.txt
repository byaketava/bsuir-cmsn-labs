cmake_minimum_required(VERSION 3.28)
project(lab4 C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(lab4
        initexit.c
        consumer.c
        producer.c
        ipc.c
        main.c
)
