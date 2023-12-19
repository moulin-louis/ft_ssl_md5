//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

//FUNCTION THAT RETURN A PTR FUNCTION OF THIS TYPE -> void (const t_ssl*) FKIN WEIRD SYNTAX
static void (* search_command(const char* str))(t_ssl*) {
  for (uint32_t i = 0; i < NBR_COMMANDS; i++) {
    if (strcmp(cmd_fn[i].command, str) == 0) {
      printf("USING %s\n", cmd_fn[i].command);
      return cmd_fn[i].fn;
    }
  }
  printf("UNKNOW COMMAND\n");
  return NULL;
}

static t_flags str_to_flags(const char* str) {
  for (uint32_t idx = 0; idx < NBR_FLAGS; idx++) {
    if (strcmp(flags_str[idx].flag_str, str) == 0)
      return flags_str[idx].flag;
  }
  return INVALID;
}

static void parsing(t_ssl** ssl, char** av, uint32_t option) {
  if (*av == NULL)
    return;
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
    case STDIN:
      if (option & QUIET)
        lst_add_back(ssl, (option & ~QUIET) | STDIN, NULL, NULL);
      else
        lst_add_back(ssl, option | STDIN, NULL, NULL);
      parsing(&lst_get_last(*ssl)->next, ++av, option);
      break;
    case STRING:
      lst_add_back(ssl, option | STRING, *(av + 1), *(av + 1));
      av += 2;
      parsing(&lst_get_last(*ssl)->next, av, option);
      break;
    case INVALID:
      for (uint32_t idx = 0; av[idx]; idx++)
        lst_add_back(ssl, option, NULL, av[idx]);
      break;
  }
}

t_ssl* parsing_args(char** av) {
  t_ssl* result = NULL;

  void (*ptr)(t_ssl*) = search_command(av[1]);
  if (ptr == NULL)
    return NULL;
  parsing(&result, &av[2], 0);
  if (result == NULL)
    return result;
  printf("Len lst: %zu\n\n", lst_len(result));
  size_t i = 0;
  //apply ptr function and print info
  for (t_ssl* tmp = result; tmp; tmp = tmp->next) {
    tmp->fn = ptr;
    printf("NODE %zu\n", i++);
    printf("FLAGS: %d\n", tmp->flags);
    printf("ARGS: %s\n", (char*)tmp->args);
    printf("\n");
  }
  return result;
}
