cmake_minimum_required(VERSION 3.25)
project(Electric VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

set(COMPILER_SRCS compiler/main.cpp compiler/utils.cpp compiler/lexer.cpp compiler/analyzer.cpp)

add_executable(Electric ${COMPILER_SRCS})
