cmake_minimum_required(VERSION 3.16)

project(MiniGit)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_executable(
    mini-git
    src/main.cpp
)