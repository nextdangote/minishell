#include "lumumbash.h"

t_token *tokenize(char *input_line) 
{
    t_token *token_list;
    char *line;

    line = strdup(input_line);
    token_list = tokenization_handler(line);
    free(line);
    return token_list;
}