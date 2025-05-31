cmake_minimum_required(VERSION 3.28)
project(FSCheck C)

set(CMAKE_C_STANDARD 11)

add_executable(FSCheck start.c
        fscheck.c
        fs.h
        types.h)

