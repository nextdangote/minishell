#include "../../include/minishell.h"

t_token *init_token(char *value, int type)
{
    t_token *token = calloc(1, sizeof(struct s_token));
    token->value = value;
    token->type = type;

    return (token);
}