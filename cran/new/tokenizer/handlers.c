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
    t_token *token = new_token(NULL, type);
    if (!token) {
        return 0;
    }
    token_list_add_back(token_list, token);
    (*line_ptr)++;
    if (type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT_REDIRECTION) {
        (*line_ptr)++;
    }
    return 1;
}

int handle_separator(char **line_ptr, t_token **token_list) 
{
    if (!strncmp(*line_ptr, "<<", 2)) {
        return append_separator(TOKEN_HEREDOC, line_ptr, token_list) && 1;
    } else if (!strncmp(*line_ptr, ">>", 2)) {
        return append_separator(TOKEN_APPEND_OUTPUT_REDIRECTION, line_ptr, token_list) && 1;
    } else if (!strncmp(*line_ptr, "<", 1)) {
        return append_separator(TOKEN_INPUT_REDIRECTION, line_ptr, token_list) && 1;
    } else if (!strncmp(*line_ptr, ">", 1)) {
        return append_separator(TOKEN_OUTPUT_REDIRECTION, line_ptr, token_list) && 1;
    } else {
        return append_separator(TOKEN_PIPE, line_ptr, token_list) && 1;
    }
}


int	append_word(char **line_ptr, t_token **token_list)
{
	char	*tmp_line;
	char	*value;
	t_token	*token;
	size_t	i;

	tmp_line = *line_ptr;
	i = 0;
	while (tmp_line[i] && !is_separator(tmp_line + i))
	{
		if (is_quote(tmp_line[i]))
		{
			if (!skip_quotes(tmp_line, &i))
				return (quote_error(tmp_line[i]), 0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = new_token(value, TOKEN_WORD);
	if (!token)
		return (free(value), 0);
	*line_ptr += i;
	return (token_list_add_back(token_list, token), 1);
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

