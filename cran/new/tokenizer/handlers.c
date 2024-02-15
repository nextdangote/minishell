#include "lumumbash.h"


t_token *new_token(char *value, t_token_type type) 
{
    t_token *new_token = (t_token *)malloc(sizeof(t_token));
    if (!new_token) {
        return NULL;
    }
    new_token->value = value;
    new_token->type = type;
    return new_token;
}


int append_separator(t_token_type type, char **line_ptr, t_token **token_list)
{
    t_token *token;
    int length;

    length = (type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT_REDIRECTION) ? 2 : 1;
    token = new_token(ft_substr(*line_ptr, 0, length), type);
    if (!token)
        return (0);
    *line_ptr += length;
    return (token_list_add_back(token_list, token), 1);
}



int handle_separator(char **line_ptr, t_token **token_list) 
{
    int length = 0;
    if (!strncmp(*line_ptr, "<<", 2)) {
        length = 2;
        return append_separator(TOKEN_HEREDOC, line_ptr, token_list) && 1;
    } else if (!strncmp(*line_ptr, ">>", 2)) {
        length = 2;
        return append_separator(TOKEN_APPEND_OUTPUT_REDIRECTION, line_ptr, token_list) && 1;
    } else if (!strncmp(*line_ptr, "<", 1)) {
        length = 1;
        return append_separator(TOKEN_INPUT_REDIRECTION, line_ptr, token_list) && 1;
    } else if (!strncmp(*line_ptr, ">", 1)) {
        length = 1;
        return append_separator(TOKEN_OUTPUT_REDIRECTION, line_ptr, token_list) && 1;
    } else {
        length = 1;
        return append_separator(TOKEN_PIPE, line_ptr, token_list) && 1;
    }
    *line_ptr += length;
}


int append_word(char **line_ptr, t_token **token_list)
{
    int i = 0;
    char *line = *line_ptr;
    int in_quotes = 0;
    char *word = malloc(strlen(line) + 1);
    int j = 0;

    while (line[i])
    {
        if (line[i] == '\\' && line[i + 1])
        {
            word[j++] = line[++i]; 
        }
        else if (line[i] == '"' || line[i] == '\'')
        {
            if (in_quotes) 
            {
                if (in_quotes == line[i]) 
                {
                    in_quotes = 0; 
                }
            }
            else
            {
                in_quotes = line[i]; 
            }
            word[j++] = line[i]; 
        }
        else if (!in_quotes && (line[i] == '<' || line[i] == '>' || line[i] == '|' || line[i] == ';'))
        {
            break; 
        }
        else
        {
            word[j++] = line[i]; 
        }
        i++;
    }
    word[j] = '\0'; 

    if (!token_list_add_back(token_list, new_token(word, TOKEN_WORD)))
        return (0);
    *line_ptr += i;
    return (1);
}


t_token *tokenization_handler(char *line) 
{
    int error = 0;
    t_token *token_list = NULL;

    while (*line) {
        if (error) {
            clear_token_list(&token_list); 
            return NULL;
        }
        if (ft_isspace(*line)) {
            skip_spaces(&line);
        } else if (!strncmp(line, "<", 1) || !strncmp(line, ">", 1) ||
                   !strncmp(line, "|", 1)) {
            error = !handle_separator(&line, &token_list);
        } else {
            error = !append_word(&line, &token_list);
        }
    }
    return token_list;
}

