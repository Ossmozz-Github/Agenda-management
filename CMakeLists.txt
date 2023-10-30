cmake_minimum_required(VERSION 3.24)
project(Agenda_management_project C)

set(CMAKE_C_STANDARD 11)

add_executable(Agenda_management_project main.c timer.h timer.c cell.c cell.h list.c list.h)
