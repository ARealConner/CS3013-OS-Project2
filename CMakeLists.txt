cmake_minimum_required(VERSION 3.27)
project(Project2 C)

set(CMAKE_C_STANDARD 17)

add_executable(Project2 src/main.c
        src/utils.c
        include/utils.h
        src/rugby.c
        include/rugby.h
        include/football.h
        src/football.c
        include/baseball.h
        src/baseball.c
        src/shared.c
        include/shared.h)