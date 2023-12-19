cmake_minimum_required(VERSION 3.22)

set(CMAKE_C_COMPILER  /usr/bin/clang)
project(ft_ssl C)

add_compile_options()
include_directories(./inc)
link_libraries(m ssl crypto)
add_executable(ft_ssl ./src/main.c
        inc/ft_ssl.h
        src/main.c
        src/parsing.c
        src/md5.c
        src/sha256.c
        utils.c
        src/execution.c)