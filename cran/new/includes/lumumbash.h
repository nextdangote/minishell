#ifndef LUMUMBASH_H
# define LUMUMBASH_H

# include <stdio.h>
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
# include "tokenizer.h"
# include "parser.h"





typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction;




// builtins
int	ft_echo(char **args);
void ft_exit(char **args);
int	ft_pwd(void);


// cleaners
void	ft_lstclear(t_list **lst, void (*del)(void *));
void	clean_shell(t_minishell *minishell);
void	clean_shell(t_minishell *minishell);
static void	ft_del(void *ptr);
void	*collector(void *ptr, bool clean);


// tree.c
static bool ft_leave_leaf(int p[2], int *pid);
static void	ft_init_leaf(t_node *node);
void ft_init_tree(t_node *node);
bool	ft_is_delimiter(char *delimiter, char *str);
void	ft_heredoc(t_redir_node *redir, int p[2]);


// pipes_exec.c
int exec_child(t_node *node);


//exec.c
int	get_exit_status(int status);
static void exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction);
static	int	exec_pipeline(t_node *tree);
int	exec_node(t_node *tree, bool piped);


// exec_utils.c
void	ft_lstadd_back(t_list **lst, t_list *new);
t_list	*ft_lstnew(void *content);
int	check_redir(t_node *node);


// exec_simple.c
void	reset_stds(bool piped);
int	exec_builtin(char **args);
bool	is_builtin(char *arg);
int	exec_simple_cmd(t_node *node, bool piped);


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
