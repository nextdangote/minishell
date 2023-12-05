#include "lumumbash.h"


void set_parse_error(t_parse_error_type type, t_minishell *minishell) 
{
    if (minishell != NULL) {
        minishell->parse_error.type = type;
    }
}


void handle_parse_error(t_minishell *minishell) 
{
    t_token_type token_type;
    char *types[] = {"TOKEN_WORD", "<", ">", "<<", ">>", "|", "newline"};

    if (minishell == NULL || minishell->parse_error.type == 0) {
        return;
    }
    if (minishell->parse_error.type == SYNTAX_ERROR) 
    {
        if (minishell->current_token == NULL) {
            token_type = TOKEN_NL;
        } else {
            token_type = minishell->current_token->type;
        }
        ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
        ft_putstr_fd(types[token_type], 2);
        ft_putstr_fd("'\n", 2);
        minishell->exit_s = 258;
    }
    ft_clear_ast(&(minishell->ast), minishell);
    ft_bzero(&(minishell->parse_error), sizeof(t_parse_error));
}
