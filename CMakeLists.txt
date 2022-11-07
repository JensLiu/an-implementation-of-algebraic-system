cmake_minimum_required(VERSION 3.23)
project(an_implementation_of_algebraic_system)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(an_implementation_of_algebraic_system
        algebraic-system-with-single-binary-operation.h
        binary-function.h
        binary-relation.h
        input-parse.h
        main.cpp
        pair.h
        set.h
        triple.h)
