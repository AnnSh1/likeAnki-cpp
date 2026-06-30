cmake_minimum_required(VERSION 3.20)

project(LikeAnki VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(like-anki
    src/main.cpp
    src/controller.cpp
    src/parser.cpp
    src/deck.cpp
)

