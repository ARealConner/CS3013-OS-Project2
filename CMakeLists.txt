cmake_minimum_required(VERSION 3.27)
project(Project2 C)

set(CMAKE_C_STANDARD 17)

add_executable(Project2 src/main.c
        src/utils.c
        include/utils.h
        src/rugby.c
        include/football.h
        src/football.c
        include/baseball.h
        src/baseball.c
        include/player.h
        src/player.c
        include/rugby.h
        src/shared.c
        include/shared.h)
