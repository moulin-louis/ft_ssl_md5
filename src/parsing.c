//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

static void parsing(t_ssl** ssl, char** av, uint32_t option) {
  if (*av == NULL) {
    if (lst_len(*ssl))
      return;
    uint8_t* input = NULL;
    uint64_t len = 0;
    read_all_file(0, &input, &len);
    if (input == NULL)
      return;
    lst_add_back(ssl, option | STDIN, (char*)input, NULL, print_stdin_args);
    lst_get_last(*ssl)->len_input = len;
    return;
  }
  const t_flags flag = str_to_flags(*av);
  switch (flag) {
  case QUIET:
    option |= QUIET;
    parsing(ssl, ++av, option);
    break;
  case REVERSE:
    option |= REVERSE;
    parsing(ssl, ++av, option);
    break;
  case STDIN: {
    uint8_t* data;
    uint64_t len;
    read_all_file(0, &data, &len);
    if (data == NULL)
      break;
    lst_add_back(ssl, option | STDIN, (char*)data, (char*)data, print_stdin_args);
    lst_get_last(*ssl)->len_input = len;
    parsing(ssl, ++av, option);
    break;
  }
  case STRING:
    lst_add_back(ssl, option | STRING, *(av + 1), *(av + 1), print_string_args);
    av += 2;
    parsing(ssl, av, option);
    break;
  case INVALID:
    for (uint32_t idx = 0; av[idx]; idx++)
      lst_add_back(ssl, option, NULL, av[idx], print_file_args);
  }
}

t_ssl* parsing_args(char** av) {
  t_ssl* result = NULL;

  void (*hash_fn)(t_ssl*) = str_to_hash_fn(av[1]);
  void (*print_fn)(t_ssl*) = str_to_print_fn(av[1]);
  if (hash_fn == NULL || print_fn == NULL) {
    printf("Wrongs commands\n");
    display_help();
    return NULL;
  }
  parsing(&result, &av[2], 0);
  if (result == NULL) {
    printf("parsing failed\n");
    return result;
  }
  for (t_ssl* node = result; node; node = node->next) {
    node->hash_fn = hash_fn;
    node->print_hash = print_fn;
  }
  return result;
}
