cmake_minimum_required(VERSION 3.7)
project(Examen_Final C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(Examen_Final affichage.c main.c define.h fichiers.c fir.c iir.c integration.c lecture.c mesure.c)