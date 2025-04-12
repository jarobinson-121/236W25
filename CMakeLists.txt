cmake_minimum_required(VERSION 3.30)
project(project_3)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(project_3
    Database.h
    DatalogProgram.h
    fsm.h
    Interpreter.h
    main.cpp
    Parameter.h
    Parser.h
    Predicate.h
    Relation.h
    Rule.h
    scanner.h
    Scheme.h
    token.h
    Tuple.h)
