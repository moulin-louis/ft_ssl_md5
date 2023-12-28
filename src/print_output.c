//
// Created by louis on 12/23/23.
//

#include "ft_ssl.h"

void print_to_upper(const char* str) {
  for (uint32_t i = 0; str[i]; ++i)
    printf("%c", toupper(str[i]));
}

void print_string_node(t_ssl* ssl) {
  print_to_upper(hash_fn_to_str(ssl->hash_fn));
  char* nl = strchr((char *)ssl->args, '\n');
  nl ? *nl = 0 : (void)nl;
  printf(" (");
  ssl->print_args(ssl);
  printf(") = ");
  ssl->print_hash(ssl);
}

void print_string_args(t_ssl* ssl) {
  printf("\"%s\"", ssl->args);
}

void print_file_node(t_ssl* ssl) {
  print_to_upper(hash_fn_to_str(ssl->hash_fn));
  printf(" (");
  ssl->print_args(ssl);
  printf(") = ");
  ssl->print_hash(ssl);
}

void print_file_args(t_ssl* ssl) {
  printf("%s", ssl->args);
}

void print_stdin_node(t_ssl* ssl) {
  printf("(");
  ssl->print_args(ssl);
  printf(")= ");
  ssl->print_hash(ssl);
}

void print_stdin_args(t_ssl* ssl) {
  if (!ssl->args) {
    printf("stdin");
    return;
  }
  char* nl = strchr((char *)ssl->args, '\n');
  nl ? *nl = 0 : (void)nl;
  if (ssl->flags & QUIET)
    printf("%s", ssl->args);
  else
    printf("\"%s\"", ssl->args);
}
