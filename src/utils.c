//
// Created by loumouli on 12/19/23.
//

#include "ft_ssl.h"

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

int32_t lst_add_back(t_ssl** lst, uint32_t flags, char* input, char* args, void* ptrint_args_fn) {
  t_ssl* new = ft_calloc(1, sizeof(t_ssl));
  if (new == NULL)
    return 1;
  new->args = (uint8_t*)args;
  new->input = (uint8_t*)input;
  if (input)
    new->len_input = ft_strlen(input);
  new->flags = flags;
  new->print_args = ptrint_args_fn;
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
  uint8_t* input = NULL;
  uint64_t len;
  read_file((char *)node->args, &input, &len);
  if (input == NULL) {
    printf("ft_ssl: %s: %s: %s\n", hash_fn_to_str(node->hash_fn), node->args, strerror(errno));
    return 1;
  }
  node->input = input;
  node->len_input = len;
  return 0;
}

t_flags str_to_flags(const char* str) {
  for (uint32_t idx = 0; idx < NBR_FLAGS; idx++) {
    if (ft_strcmp(FlagsTables[idx].flag_str, str) == 0)
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
    if (ft_strcmp(CmdHashTables[i].command, str) == 0)
      return CmdHashTables[i].fn;
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
    if (ft_strcmp(CmdPrintTables[i].command, str) == 0)
      return CmdPrintTables[i].fn;
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

void hexdump(void* data, size_t len, int32_t row) {
  if (row == 0) {
    for (size_t i = 0; i < len; i++)
      dprintf(1, "%02x ", ((uint8_t*)data)[i]);
    dprintf(1, "\n");
    return;
  }
  for (size_t i = 0; i < len; i += row) {
    for (size_t j = i; j < i + row; j++) {
      if (j == len)
        break;
      dprintf(1, "%02x ", ((uint8_t*)data)[j]);
    }
    dprintf(1, "\n");
  }
  dprintf(1, "\n");
}
