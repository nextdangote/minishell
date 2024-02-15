#include "lumumbash.h"


int	ft_isspace(char c)
{
	if (c == '\t' || c == '\n' || c == '\v'
		|| c == '\f' || c == '\r' || c == ' ')
		return (1);
	return (0);
}

void	skip_spaces(char **line)
{
	while (**line && ft_isspace(**line))
				(*line)++;
}

int	is_quote(char c)
{
	if (c == '\'' || c == '"')
		return (1);
	return (0);
}

int	is_separator(char *s)
{
	if (*s == ' ' || *s == '\t' || *s == '<' || *s == '>' || *s == '|')
		return (1);
	return (0);
}


int	skip_quotes(char *str, size_t *i)
{
    char	quote_type;

    quote_type = str[*i];
    (*i)++;
    while (str[*i] && str[*i] != quote_type)
    {
        if (str[*i] == '\\' && str[*i + 1] == quote_type)
            (*i)++;
        (*i)++;
    }
    if (str[*i] == quote_type)
    {
        (*i)++;
        return (1);
    }
    else
    {
        quote_error(quote_type);
        return (0);
    }
}


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

void	quote_error(char c)
{
	t_minishell *minishell = NULL;

	ft_putstr_fd("minishell: unexpected EOF while looking for matching `", 2);
	ft_putchar_fd(c, 2);
	ft_putstr_fd("'\n", 2);
	minishell->exit_s = 258;
}


