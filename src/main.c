//
// Created by loumouli on 12/18/23.
//

#include "ft_ssl.h"

static void display_usage(void) {
  fprintf(stderr, "usage: ft_ssl command [flags] [file/string]\n");
}

int main(int ac, char **av) {
  if (ac == 1) {
    display_usage();
    return 1;
  }

  return 0;
}