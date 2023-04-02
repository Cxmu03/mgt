cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

project(function_parser VERSION 0.0
                        DESCRIPTION "A parser for mathematical functions"
                        LANGUAGES CXX)

add_executable(main src/main.cpp
                    src/lexer.cpp src/lexer.hpp
                    src/token.cpp src/token.hpp
                    src/util.hpp
                    src/h8.hpp)
