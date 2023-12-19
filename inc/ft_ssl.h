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

typedef enum {
  STDIN,
  // -p
  QUIET,
  // -q
  REVERSE,
  // -r
  STRING,
  // -s
} t_flags;

typedef struct s_ssl {
  char* command; // CONVERT THIS TO POINTER FUNCTION
  t_flags flag; // ARRAY OF FLAG TO APPLY TO THE COMMAND
  char* input; // STRING TO HASH
  char* args; // ARG/NAME TO HASH (FILE OR STRING)
  struct s_ssl* next; // NEXT COMMAND
} t_ssl;

typedef struct {
  char* command;              // COMMAND NAME
  void (*fn)(const t_ssl*);   // POINTER TO FUNCTION ASSOCIATED TO THE COMMAND
} t_cmd;

t_ssl* parsing_args(int ac, char** av);

int execute_ssl(const t_ssl* ssl);

void cleanup_ssl(t_ssl* ssl);

void hash_md5(const t_ssl* ssl);

void hash_sha256(const t_ssl* ssl);

char* flags[4] = {"-s", "-p", "-q", "-r"};
char* commands[2] = {"md5", "sha256"};
//make array of string and pointer fn
t_cmd cmd[NBR_COMMANDS] = {
  {"md5", hash_md5},
  {"sha256", hash_sha256}};

#endif //FT_SSL_H
