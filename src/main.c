//
// Created by loumouli on 12/18/23.
//

#include "ft_ssl.h"

t_flag_str FlagsTables[NBR_FLAGS] = {
  {"-p", STDIN},
  {"-q", QUIET},
  {"-r", REVERSE},
  {"-s", STRING},
};

t_cmd_fn CmdHashTables[NBR_COMMANDS] = {
  {"md5", hash_md5},
  {"sha256", hash_sha256}
};

t_cmd_fn CmdPrintTables[NBR_COMMANDS] = {
  {"md5", print_md5},
  {"sha256", print_sha256}
};

static void display_usage(void) {
  printf("usage: ft_ssl command [flags] [file/string]\n");
}

void display_help(void) {
  printf("\nCommands:\n");
  for (uint32_t idx = 0; idx < NBR_COMMANDS; idx++) {
    printf("%s\n", CmdHashTables[idx].command);
  }
  printf("\nFlags:\n");
  for (uint32_t idx = 0; idx < NBR_FLAGS; idx++) {
    printf("%s ", FlagsTables[idx].flag_str);
  }
}

static void cleanup_ssl(t_ssl* ssl) {
  while (ssl) {
    t_ssl* tmp = ssl->next;
    if (!(ssl->flags & STRING)) {
      free(ssl->input);
    }
    free(ssl);
    ssl = tmp;
  }
}

int main(int ac, char** av) {
  if (ac == 1) {
    display_usage();
    return 1;
  }
  t_ssl* ssl = parsing_args(av);
  if (ssl == NULL)
    return 1;
  execute_ssl(ssl);
  cleanup_ssl(ssl);
  return 0;
}
