//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

static void print_result(t_ssl* ssl) {
  if (ssl->flags & QUIET) {
    ssl->print_hash(ssl);
  }
  else if (ssl->flags & REVERSE) {
    ssl->print_hash(ssl);
    printf(" %s", ssl->args);
  }
  else if (ssl->flags & STDIN)
    print_stdin_node(ssl);
  else if (ssl->flags & STRING)
    print_string_node(ssl);
  else
    print_file_node(ssl);
  printf("\n");
}

void execute_ssl(t_ssl* ssl) {
  for (t_ssl* node = ssl; node; node = node->next) {
    if (!(node->flags & STDIN) && !(node->flags & STRING))
      if (process_file(node))
        continue;
    node->hash_fn(node);
    print_result(node);
  }
}
