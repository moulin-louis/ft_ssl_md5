//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

void execute_ssl(t_ssl* ssl) {
  for (t_ssl* node = ssl; node; node = node->next) {
    //if its a file, open and read it;
    if (!(ssl->flags & STDIN) && !(ssl->flags & STRING))
      if (process_file(node))
        continue;
    node->fn(node);
  }
}