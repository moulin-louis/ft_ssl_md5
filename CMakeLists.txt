cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_COMPILER  /usr/bin/gcc)
project(ft_ssl C)

add_compile_options(-g -Wall -Wextra -Werror -O3)
include_directories(./inc)
add_executable(ft_ssl ./src/main.c
        inc/ft_ssl.h
        src/main.c
        src/parsing.c
        src/md5.c
        src/sha256.c
        src/utils.c
        src/execution.c
        src/print_output.c)