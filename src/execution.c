//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

static void print_result(t_ssl* ssl) {
  if (ssl->flags & QUIET) {
    ssl->print_fn(ssl);
  }
  else if (ssl->flags & REVERSE) {
    ssl->print_fn(ssl);
    printf(" %s", ssl->args);
  }
  else if (!(ssl->flags & STRING) && !(ssl->flags & STDIN)) {
    printf("%s(%s)= ", hash_fn_to_str(ssl->hash_fn), ssl->args);
    ssl->print_fn(ssl);
  } else {
    char* nl = strchr((char*)ssl->args, '\n');
    nl ? *nl = '\0' : 0;
    printf("%s(\"%s\")= ", hash_fn_to_str(ssl->hash_fn), ssl->args);
    ssl->print_fn(ssl);
  }
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
