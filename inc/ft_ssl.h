//
// Created by loumouli on 12/18/23.
//

#ifndef FT_SSL_H
#define FT_SSL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>

#define NBR_FLAGS 4
#define NBR_COMMANDS 2

char* flags[4] = {"-s", "-p", "-q", "-r"};
char* commands[2] = {"md5", "sha256"};

typedef enum {
  STDIN,    // -p
  QUIET,    // -q
  REVERSE,  // -r
  STRING,   // -s
} t_flags;

typedef struct s_ssl {
  char* command;  // CONVERT THIS TO POINTER FUNCTION
  t_flags flag;   // ARRAY OF FLAG TO APPLY TO THE COMMAND
  char* input;    // STRING TO HASH
  char* args;     // ARG/NAME TO HASH (FILE OR STRING)
} t_ssl;

#endif //FT_SSL_H
