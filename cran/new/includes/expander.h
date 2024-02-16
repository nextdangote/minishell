#ifndef EXPANDER_H
# define EXPANDER_H

#include "lumumbash.h"


int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strlen(char *str);
int ft_check_expand(char *str, int i, char **env);
char *ft_find_env_var_part2(char *str);
char *expander(char *str, char **env);


#endif