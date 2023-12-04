#include "lumumbash.h"


// t_token	*tokenize(char *line, int *exit_status)
// {
// 	t_token	*token_list;
// 	char	*line_copy;

// 	line_copy = strdup(line);
// 	token_list = token_handler(line_copy, exit_status);
// 	free(line_copy);
//     return (token_list);
// }


t_token *tokenize(char *input_line) 
{
    t_token *token_list;
    char *line;

    line = strdup(input_line);
    token_list = tokenization_handler(line);
    free(line);
    return token_list;
}