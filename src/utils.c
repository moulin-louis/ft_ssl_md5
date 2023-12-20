//
// Created by loumouli on 12/19/23.
//

#include "../inc/ft_ssl.h"

size_t lst_len(const t_ssl* lst) {
  size_t len = 0;
  for (const t_ssl* temp = lst; temp; temp = temp->next)
    len += 1;
  return len;
}

t_ssl* lst_get_last(t_ssl* lst) {
  if (lst == NULL)
    return NULL;
  while (lst->next)
    lst = lst->next;
  return lst;
}

int32_t lst_add_back(t_ssl** lst, uint32_t flags, char* input, char* args) {
  t_ssl* new = calloc(1, sizeof(t_ssl));
  if (new == NULL)
    return 1;
  new->args = (uint8_t *)args;
  new->input = (uint8_t *)input;
  if (input)
    new->len_input = strlen(input);
  new->flags = flags;
  if (*lst == NULL) {
    *lst = new;
    return 0;
  }
  t_ssl* last = lst_get_last(*lst);
  last->next = new;
  new->prev = last;
  return 0;
}

int32_t process_file(t_ssl* node) {
  const int fd = open((char *)node->args, O_RDONLY);
  if (fd == -1) {
    fprintf(stderr, "ft_ssl: %s: %s\n", node->args, strerror(errno));
    return 1;
  }
  uint8_t* input = read_all_file(fd);
  if (input == NULL) {
    fprintf(stderr, "ft_ssl: %s: %s\n", node->args, strerror(errno));
    return 1;
  }
  node->input = input;
  node->len_input = strlen((char *)input);
  return 0;
}

uint8_t* read_all_file(const int fd) {
  char* result = strdup("");
  if (result == NULL)
    return NULL;
  while (1) {
    char buf[2096];
    const ssize_t ret = read(fd, buf, 2095);
    if (ret == -1) {
      printf("ERROR READING FILE\n");
      return NULL;
    }
    if (ret == 0)
      break;
    buf[ret] = '\0';
    char* tmp = realloc(result, strlen(result) + strlen(buf) + 1);
    if (tmp == NULL) {
      printf("ERROR ALLOCATING MEMORY\n");
      return NULL;
    }
    result = tmp;
    memcpy(result + strlen(result), buf, strlen(buf) + 1);
  }
  return (uint8_t *)result;
}

t_flags str_to_flags(const char* str) {
  for (uint32_t idx = 0; idx < NBR_FLAGS; idx++) {
    if (strcmp(FlagsTables[idx].flag_str, str) == 0)
      return FlagsTables[idx].flag;
  }
  return INVALID;
}

char* flag_to_str(const t_flags flag) {
  for (uint32_t idx = 0; idx < NBR_FLAGS; idx++) {
    if (FlagsTables[idx].flag == flag)
      return FlagsTables[idx].flag_str;
  }
  return NULL;
}

//FUNCTION THAT RETURN A PTR FUNCTION OF THIS TYPE -> void (const t_ssl*) FKIN WEIRD SYNTAX
void (* str_to_hash_fn(const char* str))(t_ssl*) {
  for (uint32_t i = 0; i < NBR_COMMANDS; i++) {
    if (strcmp(CmdHashTables[i].command, str) == 0) {
      return CmdHashTables[i].fn;
    }
  }
  return NULL;
}

char* hash_fn_to_str(void (*fn_hash)(t_ssl*)) {
  for (uint32_t i = 0; i < NBR_COMMANDS; i++) {
    if (fn_hash == CmdHashTables[i].fn)
      return CmdHashTables[i].command;
  }
  return NULL;
}

//FUNCTION THAT RETURN A PTR FUNCTION OF THIS TYPE -> void (const t_ssl*) FKIN WEIRD SYNTAX
void (* str_to_print_fn(const char* str))(t_ssl*) {
  for (uint32_t i = 0; i < NBR_COMMANDS; i++) {
    if (strcmp(CmdPrintTables[i].command, str) == 0) {
      return CmdPrintTables[i].fn;
    }
  }
  return NULL;
}

char* print_fn_to_str(void (*fn_print)(t_ssl*)) {
  for (uint32_t i = 0; i < NBR_COMMANDS; i++) {
    if (fn_print == CmdPrintTables[i].fn)
      return CmdPrintTables[i].command;
  }
  return NULL;
}
