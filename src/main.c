//
// Created by loumouli on 12/18/23.
//

#include "ft_ssl.h"

static void display_usage(void) {
  fprintf(stderr, "usage: ft_ssl command [flags] [file/string]\n");
}

int main(int ac, char** av) {
  if (ac == 1) {
    display_usage();
    return 1;
  }
  t_ssl* ssl = parsing_args(ac, av);
  if (ssl == NULL) {
    display_usage();
    return 1;
  }
  // execute_ssl(ssl);
  // cleanup_ssl(ssl);
  return 0;
}
