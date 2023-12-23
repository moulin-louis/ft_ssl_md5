//
// Created by louis on 12/23/23.
//

#include "ft_ssl.h"

void print_string_node(t_ssl* ssl) {
  print_to_upper(hash_fn_to_str(ssl->hash_fn));
  char *nl = strchr((char *)ssl->args, '\n');
  nl ? *nl = 0 : (void)nl;
  printf(" (\"%s\") = ", ssl->args);
  ssl->print_hash(ssl);
}

void print_file_node(t_ssl* ssl) {
  print_to_upper(hash_fn_to_str(ssl->hash_fn));
  printf(" (%s) = ", ssl->args);
  ssl->print_hash(ssl);

}

void print_stdin_node(t_ssl* ssl) {
  if (!ssl->args) {
    printf("(stdin)= ");
    ssl->print_hash(ssl);
    return;
  }
  char *nl = strchr((char*)ssl->args, '\n');
  nl ? *nl = 0 : (void)nl;
  printf("(\"%s\")= ", ssl->args);
  ssl->print_hash(ssl);
}