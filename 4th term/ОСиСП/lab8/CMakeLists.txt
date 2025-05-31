cmake_minimum_required(VERSION 3.28)
project(lab8)

set(CMAKE_CXX_STANDARD 11)

add_executable(lab8
        Client/client.cpp
        Server/server.cpp)
