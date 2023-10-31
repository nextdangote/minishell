#ifndef MINISHELL_H
# define MINISHELL_H
# define MAX(a, b)\
    a > b ? a : b
# define MIN(a, b)\
    a < b ? a : b
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <fcntl.h>
# include <errno.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <dirent.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>

//# define PIPE 3
// # define 
// # define
// # define
/* typedef struct s_parser
{
    s_simple_command  *simple_cmd;
    s_command_suffix  *cmdsuffix;
    s_pipe_sequence *pipeseq;
    s_token *token;
}   t_parser;

typedef struct s_simple_command
{
    s_command_name  *cmdname;
    s_command_suffix  *cmdsuffix;
    s_pipe_sequence *pipeseq;
    s_token *token;
}   t_simple_command;

typedef struct s_command_suffix
{
    s_command_name  *cmdname;
    s_command_suffix  *cmdsuffix;
    s_pipe_sequence *pipeseq;
    s_token *token;
}   t_command_suffix;

typedef struct s_pipe_sequence
{
    s_command_name  *cmdname;
    s_command_suffix  *cmdsuffix;
    s_pipe_sequence *pipeseq;
    s_token *token;
    *left element of tree
    *right element of tree
    type
}   t_pipe_sequence;*/

typedef struct s_token
{
    char *value;
    enum
    {
        TOKEN_ID,
        TOKEN_EQUALS,
        TOKEN_COLON,
        TOKEN_COMMA,
        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,
        TOKEN,
        TOKEN_INT,
        TOKEN_EOF,
    } type;
}   t_token;

typedef struct s_lexer
{
    char *src;
    char c;
    unsigned int i;
    int src_size;
}   t_lexer;

t_lexer *init_lexer(char *src);
void    tac_compile(char *src);
void lexer_advance(t_lexer *lexer);
t_token *lexer_next_token(t_lexer *lexer);
t_token *lexer_advance_with(t_lexer *lexer, t_token *token);
t_token *lexer_parse_id(t_lexer *lexer);
void lexer_skip_whitespace(t_lexer *lexer);
char lexer_peek(t_lexer *lexer, int offset);
#endif

