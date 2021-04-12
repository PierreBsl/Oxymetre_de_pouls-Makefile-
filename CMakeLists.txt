cmake_minimum_required(VERSION 3.7)
project(Examen_Final C)

set(CMAKE_C_STANDARD 99)
set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")

add_executable(Examen_Final affichage.c affichage.h main.c define.h fichiers.c fichiers.h fir.c fir.h iir.c iir.h integration.c integration.h lecture.c lecture.h mesure.c mesure.h)