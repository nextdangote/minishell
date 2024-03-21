#include "lumumbash.h"

// char	*ft_substr(char const *s, unsigned int start, size_t len)
// {
// 	char	*substr;
// 	size_t	slen;
// 	size_t	i;

// 	if (!s)
// 		return (NULL);
// 	slen = ft_strlen(s);
// 	if (!slen || start > slen - 1)
// 		return (ft_strdup(""));
// 	i = 0;
// 	while (s[start + i] && i + 1 <= len)
// 		i++;
// 	substr = ft_calloc((i + 1), sizeof(char));
// 	if (!substr)
// 		return (NULL);
// 	i = 0;
// 	while (i < len && s[start + i])
// 	{
// 		substr[i] = s[start + i];
// 		i++;
// 	}
// 	return (substr);
// }

char	*ft_extract_key(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (collector(ft_substr(str, 0, i), false));
		i++;
	}
	return (ft_strdup(str));
}


bool	ft_env_entry_exists(char *key, t_minishell *minishell)
{
	t_env	*envlst;
	

	envlst = minishell->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (true);
		envlst = envlst->next;
	}
	return (false);
}



int	ft_keycheck(char *str)
{
	int	i;

	i = 1;
	if (!ft_isalpha(*str) && *str != '_')
		return (0);
	while (str[i] && str[i] != '=')
	{
		if (!ft_alphanum(str[i]) && str[i] != '_')
			return (0);
		i++;
	}
	return (1);
}

void	ft_envlst_back(t_env *new, t_minishell *minishell)
{
	t_env	*curr;

	if (!minishell->envlst)
	{
		minishell->envlst = new;
		return ;
	}
	curr = minishell->envlst;
	while (curr && curr->next)
		curr = curr->next;
	curr->next = new;
}



char	*ft_extract_value(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
		{
			i++;
			return (collector(
					ft_substr(str, i, ft_strlen(str) - i), false));
		}
		i++;
	}
	return (NULL);
}
