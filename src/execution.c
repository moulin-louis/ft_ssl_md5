//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

static void print_result(t_ssl* ssl) {
  if (ssl->flags & QUIET) {
    if (ssl->flags & STDIN && ssl->args) {
      ssl->print_args(ssl);
      printf("\n");
    }
    ssl->print_hash(ssl);
  }
  else if (ssl->flags & REVERSE && !(ssl->flags & STDIN)) {
    ssl->print_hash(ssl);
    printf(" ");
    ssl->print_args(ssl);
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
      if (process_file(node)) //if process_file return 1, we skip this node
        continue;
    node->hash_fn(node); //hash the node, cant really fail
    print_result(node); //print the result
  }
}
