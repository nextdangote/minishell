#ifndef LUMUMBASH_H
# define LUMUMBASH_H

# include <stdio.h>
#include <stdlib.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <termios.h>
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <stdint.h>
# include <string.h>
#include <ctype.h>
# include "tokenizer.h"
# include "parser.h"

#define MAX_NUM_ARGS 100







typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction;




// builtins
int	ft_echo(char **args);
// void ft_exit(char **args);
void ft_exit(char **args, t_minishell *minishell);
int ft_pwd(void);
//
// void ft_init_envlst(void);
// int ft_env(void);
void ft_init_envlst(t_minishell *minishell);
int ft_env(t_minishell *minishell);
//

int ft_unset(char **args, t_minishell *minishell);
//
// void ft_update_envlst(char *key, char *value, bool create);
void ft_update_envlst(char *key, char *value, bool create, t_minishell *minishell);
// int ft_export(char **argv);
int ft_export(char **argv, t_minishell *minishell);

//



//help
size_t ft_strlen(const char *str);
int ft_strncmp(const char *s1, const char *s2, size_t n);
int ft_strcmp(const char *s1, const char *s2);
// void ft_putchar_fd(char c, int fd);
// void ft_putstr_fd(char *s, int fd);
int ft_isalpha(int c);
int ft_isdigit(int c);
int ft_alphanum(int c);

void *ft_memset(void *b, int c, size_t len);
void *ft_calloc(size_t count, size_t size);
void *ft_memcpy(void *dst, const void *src, size_t n);
char *ft_strdup(const char *s1);


// char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_extract_key(char *str);
// bool ft_env_entry_exists(char *key);
bool ft_env_entry_exists(char *key, t_minishell *minishell);

int ft_keycheck(char *str);
// void ft_envlst_back(t_env *new);
void ft_envlst_back(t_env *new, t_minishell *minishell);

char *ft_extract_value(char *str);


// cleaners
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	clean_shell(t_minishell *minishell);
void	clean_shell(t_minishell *minishell);
// static void	ft_del(void *ptr);
void	*collector(void *ptr, bool clean);
void ft_free_char2(char **tofree); // added after expander

// tree.c
// static bool ft_leave_leaf(int p[2], int *pid);
// static void	ft_init_leaf(t_node *node);
void ft_init_tree(t_node *node);
// static void ft_init_leaf(t_minishell *minishell, t_node *node);
// void ft_init_tree(t_minishell *minishell, t_node *node);
bool	ft_is_delimiter(char *delimiter, char *str);
void	ft_heredoc(t_redir_node *redir, int p[2]);


// pipes_exec.c
int exec_child(t_node *node);


//exec.c
int	get_exit_status(int status);
// static void exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction, t_minishell *minishell);
// static int exec_pipeline(t_node *tree, t_minishell *minishell);

// static void exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction);
// static	int	exec_pipeline(t_node *tree);

// int	exec_node(t_node *tree, bool piped);
int exec_node(t_node *tree, bool piped, t_minishell *minishell);

// exec_utils.c
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int	check_redir(t_node *node);


// exec_simple.c
void	reset_stds(bool piped);
// int	exec_builtin(char **args);
int exec_builtin(char **args, t_minishell *minishell);
bool is_builtin(char *arg);
// int	exec_simple_cmd(t_node *node, bool piped);
int exec_simple_cmd(t_node *node, bool piped, t_minishell *minishell);

// errors.c
int	error_msg(t_error error);


// checks.c
t_error	ft_check_exec(char *file, bool cmd);
t_error	ft_check_read(char *file);
t_error	ft_check_write(char *file);


// exec_redir.c
int ft_out(t_redir_node *redir_list, int *status);
int ft_in(t_redir_node *redir_list, int *status);
int ft_append(t_redir_node *redir_list, int *status);


#endif
