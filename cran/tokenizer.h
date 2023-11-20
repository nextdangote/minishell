#ifndef TOKENIZER_H
# define TOKENIZER_H


#include "minishell.h"
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

typedef enum e_token_type
{
    TOKEN_WORD, // cmd
    TOKEN_PIPE, // |
    TOKEN_INPUT_REDIRECTION, // <
    TOKEN_OUTPUT_REDIRECTION, // >
    TOKEN_APPEND_OUTPUT_REDIRECTION, // >>
    TOKEN_HEREDOC, // <<
    TOKEN_NL // \n

} t_token_type;

typedef struct s_token
{
	t_token_type		type;
	char				*value;
	struct s_token		*next;
	struct s_token		*prev;
}	t_token;

// tokenizer.c

void	ft_putchar_fd(char c, int fd);
char	*ft_substr(char const *s, unsigned int start, size_t len);
void	ft_putstr_fd(char *s, int fd);

int	is_space(char c);
void    skip_spaces(char **line);
int	is_quote(char c);
int	is_separator(char *s);
bool	skip_quotes(char *line, size_t *i);
void	quote_error(char c, int *exit_status);

t_token	*new_token(char *value, t_token_type type);
void	add_to_list(t_token **lst, t_token *new_token);
void	clear_token_list(t_token **list);

int	append_separator(t_token_type type, char **line_ptr, t_token **token_list);
int	separator(char **line_ptr, t_token **token_list);
int	append_word(char **line_ptr, t_token **token_list, int *exit_status);

t_token	*token_handler(char *line, int *exit_status);
t_token	*tokenize(char *line, int *exit_status);

#endif