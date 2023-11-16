#include "tokenizer.h"
#include "minishell.h"
#include "parser.h"
#include "header.h"


/// the tokenizer logic: initially consider the liine. In the line, check if there are separators. If there are, then separate the line by separator, and create tokens of each individual part. the result of tokenizing is dividing the line into word and separator tokens only. If there are no separators, then the whole line is a token. After the separator, the word tokens are the arguments, and the separator tokens are the operators.


// tokenizer helpers

void	ft_putchar_fd(char c, int fd)
{
	write(fd, &c, 1);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*substr;
	size_t	slen;
	size_t	i;

	if (!s)
		return (NULL);
	slen = strlen(s);
	if (!slen || start > slen - 1)
		return (strdup(""));
	i = 0;
	while (s[start + i] && i + 1 <= len)
		i++;
	substr = calloc((i + 1), sizeof(char));
	if (!substr)
		return (NULL);
	i = 0;
	while (i < len && s[start + i])
	{
		substr[i] = s[start + i];
		i++;
	}
	return (substr);
}
void	ft_putstr_fd(char *s, int fd)
{
	if (s)
		while (*s)
        {
			ft_putchar_fd(*s++, fd);
            usleep(100000);
        }
}

// is it a space?
int	is_space(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}
// skip spaces
void    skip_spaces(char **line)
{
	while (**line && is_space(**line))
				(*line)++;
}
// is it a quote?
int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}
// is it a separator?
int	is_separator(char *s)
{
	if (*s == ' ' || *s == '\t' || *s == '<' || *s == '>' || *s == '|')
		return (1);
	return (0);
}
// skip quotes
bool	skip_quotes(char *line, size_t *i)
{
	char	quote;

	quote = line[*i];
	if (strchr(line + *i + 1, quote))
	{
		(*i)++;
		while (line[*i] != quote)
			(*i)++;
		(*i)++;
		return (true);
	}
	return (false);
}
// in case of quotes not in pair
void	quote_error(char c, int *exit_status)
{
	ft_putstr_fd("lumumbash error: Unmatched quotes in the input\n", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	*exit_status = 2; // might be different when adding signal handling. this for when an unexpected eof is met like in quotes not in pair
}

// creates a new token
t_token	*new_token(char *value, t_token_type type)
{
	t_token	*new_token;

	new_token = (t_token *)calloc(1, sizeof(t_token));
	if (!new_token)
		return (NULL);
	new_token->value = value;
	new_token->type = type;
	return (new_token);
}

// adds a token to the token list
void	add_to_list(t_token **list, t_token *new_token)
{
	t_token	*current_node;

	if (!*list)
	{
		*list = new_token;
		return ;
	}
	current_node = *list;
	while (current_node && current_node -> next)
		current_node = current_node -> next;
	current_node -> next = new_token;
	new_token -> prev = current_node;
}

// clears the token list
void	clear_token_list(t_token **list)
{
	t_token	*current_node;
	t_token	*next;

	current_node = *list;
	if (!current_node)
		return ;
	while (current_node)
	{
		free(current_node->value);
		next = current_node->next;
		free(current_node);
		current_node = next;
	}
	*list = NULL;
}

// Adds a separator token to the token list : 
int	append_separator(t_token_type type, char **line_ptr,
	t_token **token_list)
{
	t_token	*token;

	token = new_token(NULL, type); // empty separator type token
	if (!token)
		return (0);
	add_to_list(token_list, token);
	(*line_ptr)++;
	if (type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT_REDIRECTION)
		(*line_ptr)++; // for << and >> double increment because they are 2 chars
	return (1);
}

// Adds a word token to the token list
int	append_word(char **line_ptr, t_token **token_list, int *exit_status)
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
				quote_error(tmp_line[i], exit_status);
                return (0);
		}
		else
			i++;
	}
	value = ft_substr(tmp_line, 0, i);
	if (!value)
		return (0);
	token = new_token(value, TOKEN_WORD);
	if (!token)
    {
        free(value);
		return (0);
    }
	*line_ptr += i;
	return (add_to_list(token_list, token), 1);
}

// Handles different separator cases
int	separator(char **line_ptr, t_token **token_list)
{
	if (!strncmp(*line_ptr, "<<", 2))
		return (append_separator(TOKEN_HEREDOC, line_ptr, token_list) && 1);
	else if (!strncmp(*line_ptr, ">>", 2))
		return (append_separator(TOKEN_APPEND_OUTPUT_REDIRECTION, line_ptr, token_list) && 1);
	else if (!strncmp(*line_ptr, "<", 1))
		return (append_separator(TOKEN_INPUT_REDIRECTION, line_ptr, token_list) && 1);
	else if (!strncmp(*line_ptr, ">", 1))
		return (append_separator(TOKEN_OUTPUT_REDIRECTION, line_ptr, token_list) && 1);
	else
		return (append_separator(TOKEN_PIPE, line_ptr, token_list) && 1);
}

// goes through the line until \0, classify parts as separator or word and create tokens of them, or return NULL if there is an error
t_token	*token_handler(char *line, int *exit_status)
{
	int		error;
	t_token	*token_list;

	error = 0;
	token_list = NULL;
	while (*line)
	{
		if (error)
        {
            clear_token_list(&token_list);
            return NULL;
        }
		if (is_space(*line))
			skip_spaces(&line);
		else if (!strncmp(line, "<", 1) || !strncmp(line, ">", 1)
			|| !strncmp(line, "|", 1))
			error = (!separator(&line, &token_list) && 1);
		else
			error = (!append_word(&line, &token_list, exit_status) && 1);
	}
	return (token_list);
}

//main tokenizing function
t_token	*tokenize(char *line, int *exit_status)
{
	t_token	*token_list;
	char	*line_copy;

	line_copy = strdup(line);
	token_list = token_handler(line_copy, exit_status);
	free(line_copy);
    return (token_list);
}