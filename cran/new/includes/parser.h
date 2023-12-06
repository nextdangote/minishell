#ifndef PARSER_H
# define PARSER_H

#include "lumumbash.h"



typedef enum e_node_type
{
	NODE_PIPE,
	NODE_CMD,
	NODE_UNKNOWN
}	t_node_type;

typedef enum e_redir_type
{
	REDIR_IN,
	REDIR_OUT,
	REDIR_HEREDOC,
	REDIR_APPEND
}	t_redir_type;

typedef enum e_parse_err_type
{
	MALLOC_ERROR = 1,
	SYNTAX_ERROR,
}	t_parse_error_type;

typedef struct s_redir_node
{
	t_redir_type			type;
	char				*value;
	char				**expanded_value;
	int					here_doc;
	struct s_redir_node	*prev;
	struct s_redir_node	*next;
}	t_redir_node;

typedef struct s_node
{
	t_node_type			type;
	t_redir_node			*redir_list;
	char				*args;
	struct s_node		*left;
	struct s_node		*right;
    char *value;  //added for main testing
}	t_node;

typedef struct s_parse_error
{
	t_parse_error_type	type;
	char				*str;
}	t_parse_error;

typedef struct s_minishell
{
	char			*line;
	t_token			*tokens;
	t_token			*current_token;
	t_node			*ast;
	int				exit_s;
	t_parse_error		parse_error;
	int				stdin;
	int				stdout;
	struct termios	original_term;
	char			**environ;
}					t_minishell;

// nodes.c
void	ft_bzero(void *s, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
t_node_type	get_node_type(t_token_type type);
t_redir_type	get_redir_type(t_token_type type);
t_node	*new_node(t_node_type type);
t_redir_node	*new_redir_node(t_token_type type, char *value);
void	append_redir_node(t_redir_node **list, t_redir_node *new);


// parser_errors.c
// void set_parse_error(t_parse_error_type type, t_minishell *minishell);

void set_parse_error(t_parse_error_type type);
void handle_parse_error(t_minishell *minishell);

// parser_helpers.c
static t_node *get_simple_cmd(t_minishell *minishell);
t_node	*ft_term(t_minishell *minishell);
t_node	*ft_combine(t_token_type op, t_node *left, t_node *right, t_minishell *minishell);
t_node	*ft_expression(t_minishell *minishell);

// parser_utils.c
bool	current_token_is_op(t_minishell *minishell);
void	get_next_token(t_minishell *minishell);
void	ft_clear_redir_list(t_redir_node **list);
void	ft_clear_cmd_node(t_node *node);
void	ft_recursive_clear_ast(t_node *node);
void	ft_clear_ast(t_node **ast, t_minishell *minishell);
bool	is_redir(t_token_type type);
char	*ft_strjoin_with(char const *s1, char const *s2, char c);
bool	ft_join_args(char **args, t_minishell *minishell); 
bool	get_redir_list(t_redir_node **redir_list, t_minishell *minishell);

// parser.c
t_node	*ft_parse(t_minishell *minishell);


#endif
