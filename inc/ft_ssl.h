//
// Created by loumouli on 12/18/23.
//

#pragma once
#ifndef FT_SSL_H
#define FT_SSL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdint.h>
#include <errno.h>

#define NBR_FLAGS 4
#define NBR_COMMANDS 2

typedef enum {
  INVALID = 0,
  // invalid flag , value of 0, enum == 0
  STDIN = 1 << 1,
  // -p (read from stdin), enum == 1
  QUIET = 1 << 2,
  // -q (quiet mode -> only print the hash), enum == 2
  REVERSE = 1 << 3,
  // -r (reverse the format of the output), enum == 4
  STRING = 1 << 4,
  // -s (print the hash of the given string), enum == 8
} t_flags;

typedef struct s_ssl {
  void (*hash_fn)(struct s_ssl*); // POINTER TO FUNCTION USED TO HASH THE INPUT
  void (*print_fn)(struct s_ssl*); // POINTER TO FUNCTION USED TO PRINT THE RESULT
  uint32_t flags; // FLAGS TO APPLY TO THE COMMAND/OUTPUT
  uint8_t* input; // STRING TO HASH
  uint64_t len_input; //LEN OF INPUT
  uint8_t* args; // ARG/NAME TO HASH (FILE OR STRING)
  uint8_t hash[128]; // HASHED RESULT
  struct s_ssl* next; // NEXT COMMAND
  struct s_ssl* prev; // PREVIOUS COMMAND
} t_ssl;

typedef struct {
  char* command; // COMMAND NAME
  void (*fn)(t_ssl*); // POINTER TO FUNCTION ASSOCIATED TO THE COMMAND
} t_cmd_fn;

typedef struct {
  char* flag_str;
  t_flags flag;
} t_flag_str;

t_ssl* parsing_args(char** av);

void execute_ssl(t_ssl* ssl);

void hash_md5(t_ssl* ssl);

void print_md5(t_ssl* ssl);

void hash_sha256(t_ssl* ssl);

void print_sha256(t_ssl* ssl);

size_t lst_len(const t_ssl* lst);

int32_t lst_add_back(t_ssl** lst, uint32_t flags, char* input, char* args);

t_ssl* lst_get_last(t_ssl* lst);

uint8_t* read_all_file(int fd);

int32_t process_file(t_ssl* node);

t_flags str_to_flags(const char* str);

char* flag_to_str(t_flags flag);

void (*str_to_hash_fn(const char* str))(t_ssl*);

char* hash_fn_to_str(void (*fn_hash)(t_ssl*));

void (*str_to_print_fn(const char* str))(t_ssl*);

char* print_fn_to_str(void (*fn_print)(t_ssl*));

extern t_cmd_fn CmdHashTables[NBR_COMMANDS];
extern t_cmd_fn CmdPrintTables[NBR_COMMANDS];
extern t_flag_str FlagsTables[NBR_FLAGS];

#endif //FT_SSL_H
