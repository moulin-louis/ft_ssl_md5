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

int32_t lst_add_back(t_ssl** lst, uint32_t flags, char* input, char* args) {
  t_ssl* new = calloc(1, sizeof(t_ssl));
  if (new == NULL)
    return 1;
  new->args = (uint8_t*)args;
  new->input = (uint8_t*)input;
  new->flags = flags;
  if (*lst == NULL) {
    *lst = new;
    return 0;
  }
  lst_get_last(*lst)->next = new;
  return 0;
}

int32_t process_file(t_ssl* node) {
  const int fd = open((char*)node->args, O_RDONLY);
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
  return 0;
}

uint8_t *read_all_file(const int fd) {
  char *result = strdup("");
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
    char *tmp = realloc(result, strlen(result) + strlen(buf) + 1);
    if (tmp == NULL) {
      printf("ERROR ALLOCATING MEMORY\n");
      return NULL;
    }
    result = tmp;
    memcpy(result + strlen(result), buf, strlen(buf) + 1);
  }
  return (uint8_t*)result;
}