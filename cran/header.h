#ifndef HEADER_H
# define HEADER_H

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
#include "tokenizer.h"
#include "minishell.h"
#include "parser.h"
#include "header.h"

typedef struct s_node t_node;
typedef struct s_minishell t_minishell;
typedef enum e_error_msg t_error_msg;
typedef enum e_error_no t_error_no;
typedef enum e_ast_direction t_ast_direction;
typedef struct s_err t_err;
typedef struct s_path t_path;
typedef struct s_list t_list;
typedef enum e_token_type t_token_type;
typedef enum e_node_type t_node_type;
typedef enum e_redir_type t_redir_type;
typedef enum e_parse_err_type t_parse_error_type;
typedef struct s_redir_node t_redir_node;
typedef struct s_token t_token;
typedef struct s_parse_error t_parse_error;


// typedef enum 
// {
//     TOKEN_WORD, // cmd
//     TOKEN_PIPE, // |
//     TOKEN_INPUT_REDIRECTION, // <
//     TOKEN_OUTPUT_REDIRECTION, // >
//     TOKEN_APPEND_OUTPUT_REDIRECTION, // >>
//     TOKEN_HEREDOC, // <<
//     TOKEN_NL // \n

// } t_token_type;

// typedef struct s_token
// {
// 	t_token_type		type;
// 	char				*value;
// 	struct s_token		*next;
// 	struct s_token		*prev;
// }	t_token;


// typedef enum e_node_type
// {
// 	NODE_PIPE,
// 	NODE_CMD
// }	t_node_type;


// typedef enum e_redir_type
// {
// 	REDIR_IN,
// 	REDIR_OUT,
// 	REDIR_HEREDOC,
// 	REDIR_APPEND
// }	t_redir_type;

// typedef enum e_parse_err_type
// {
// 	MALLOC_ERROR = 1,
// 	SYNTAX_ERROR,
// }	t_parse_error_type;

// typedef struct s_redir_node
// {
// 	t_redir_type			type;
// 	char				*value;
// 	char				**expanded_value;
// 	int					here_doc;
// 	struct s_redir_node	*prev;
// 	struct s_redir_node	*next;
// }	t_redir_node;

// typedef struct s_node
// {
// 	t_node_type			type;
// 	t_redir_node			*redir_list;
// 	char				*args;
// 	char				**expanded_args;
// 	struct s_node		*left;
// 	struct s_node		*right;
// }	t_node;

// typedef struct s_parse_error
// {
// 	t_parse_error_type	type;
// 	char				*str;
// }	t_parse_error;


// typedef struct s_minishell
// {
// 	char			*line;
// 	t_token			*tokens;
// 	t_token			*current_token;
// 	t_node			*ast;
// 	int				exit_s;
// 	// bool			signint_child;
// 	t_parse_error		parse_error;
// 	int				stdin;
// 	int				stdout;
// 	char			**environ;
// 	// t_env			*envlst;
// 	bool			heredoc_sigint;
// 	struct termios	original_term;
// }					t_minishell;

typedef enum e_error_msg
{
	CMD_NOT_FOUND,
	NO_SUCH_FILE,
	PERMISSION_DENIED,
	AMBIGUOUS,
	TOO_MANY_ARGS,
	NUMERIC_REQUIRED
}	t_error_msg;

typedef enum e_error_no
{
	SUCCESS,
	GENERAL,
	CANT_EXECUTE = 126,
	NOT_FOUND,
	ENO_EXEC_255 = 255
}	t_error_no;

typedef enum e_ast_direction
{
	TD_LEFT,
	TD_RIGHT
}	t_ast_direction;

typedef struct s_err
{
	t_error_no	no;
	t_error_msg	msg;
	char		*cause;
}	t_error;

typedef struct s_path
{
	t_error	error;
	char	*path;
}	t_path;


typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

// // tokenizer.c

// void	ft_putchar_fd(char c, int fd);
// char	*ft_substr(char const *s, unsigned int start, size_t len);
// void	ft_putstr_fd(char *s, int fd);

// int	is_space(char c);
// void    skip_spaces(char **line);
// int	is_quote(char c);
// int	is_separator(char *s);
// bool	skip_quotes(char *line, size_t *i);
// void	quote_error(char c, int *exit_status);

// t_token	*new_token(char *value, t_token_type type);
// void	add_to_list(t_token **lst, t_token *new_token);
// void	clear_token_list(t_token **list);

// int	append_separator(t_token_type type, char **line_ptr, t_token **token_list);
// int	separator(char **line_ptr, t_token **token_list);
// int	append_word(char **line_ptr, t_token **token_list, int *exit_status);

// t_token	*token_handler(char *line, int *exit_status);
// t_token	*tokenize(char *line, int *exit_status);


// //parser.c

// char	*ft_strjoin(char const *s1, char const *s2);
// char	*ft_strjoin_with(char const *s1, char const *s2, char c);
// void	ft_free_ch(char **tofree);
// void	ft_bzero(void *s, size_t n);

// void	get_next_token(t_minishell *minishell);
// bool	current_token_is_redir(t_minishell *minishell);
// bool	is_redir(t_token_type type);
// bool	ft_join_args(char **args, t_minishell *minishell);

// void	clear_cmd_node(t_node *node);
// void	recursive_clear_ast(t_node *node);
// void	clear_redir_list(t_redir_node **list);
// void	clear_cmd_node(t_node *node);
// void	clear_token_list(t_token **list);
// void	clear_ast(t_node **ast, t_token **tokens);

// void	set_parse_error(t_parse_error_type type, t_minishell *minishell);
// void	handle_parse_error(t_minishell *minishell);

// t_node	*new_node(t_node_type type);
// t_redir_node	*new_redir_node(t_token_type type, char *value);
// t_redir_type	get_redir_type(t_token_type type);
// bool	get_redir_list(t_redir_node **redir_list, t_minishell *minishell);
// void	append_redir_node(t_redir_node **list, t_redir_node *new);
// t_node_type	get_node_type(t_token_type type);
// // t_redir_type	get_redir_type(t_token_type type);



// t_node *ft_combine(t_token_type op, t_node *left, t_node *right, t_minishell *minishell);
// t_node	*ft_term(t_minishell *minishell);
// t_node	*get_simple_cmd(t_minishell *minishell);
// t_node *ft_expression(t_minishell *minishell);
// t_node	*ft_parse(t_minishell *minishell);


// exec.c
// void	ft_putstr_fd(char *s, int fd);
// void	ft_putchar_fd(char c, int fd);

void	ft_putnbr_fd(int n, int fd);
static void	ft_del(void *ptr);
void	clear_list(t_list **list, void (*del)(void *));
void	*to_trash(void *ptr, bool clean);
bool	in_parallel(char *delimiter, char *str);
void	list_add(t_list **list, t_list *new);
t_list	*new_in_list(void *content);
bool	ft_is_builtin(char *arg);
int	exec_builtin(char **args);
int	exec_simple_cmd(t_node *node, bool piped, t_minishell *minishell);


int	error_msg(t_error error);
t_error	check_write(char *file);
t_error	check_exec(char *file, bool cmd);
t_error	check_read(char *file);
void	clean_shell(t_minishell *minishell);
int	get_exit_status(int status);
static int	exec_child(t_node *node, t_minishell *minishell);
static int	heredoc_expand_writer(char *str, size_t i, int fd, int exit_status);
void	heredoc_expander(char *str, int fd, int exit_status);
bool	is_delimiter(char *delimiter, char *str);
void	ft_heredoc(t_redir_node *redir, int p[2], t_minishell *minishell);
static bool ft_leave_leaf(int p[2], int *pid);
static void	ft_init_leaf(t_node *node, t_minishell *minishell);
void	ft_init_tree(t_node *node, t_minishell *minishell);


int	ft_out(t_redir_node *redir_list, int *status);
int	ft_in(t_redir_node *redir_list, int *status);
int	ft_append(t_redir_node *redir_list, int *status);
static void exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction, t_minishell *minishell);
static	int	exec_pipeline(t_node *tree, t_minishell *minishell);
int	exec_node(t_node *tree, bool piped, t_minishell *minishell);


int	check_redir(t_node *node);
void	reset_stds(bool piped);
int	error_msg(t_error error);

// builtins.c


int	ft_pwd(void);
int	ft_echo(char **args);

// main.c
static void	ft_init_minishell(t_minishell *minishell, char **env);
static void	start_execution(t_minishell *minishell);


#endif