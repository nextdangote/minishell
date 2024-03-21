#include "lumumbash.h"


static void	ft_unset_helper(t_minishell	*minishell, char *key)
{
	t_env	*current;
	t_env	*prev;
	

	prev = NULL;
	current = minishell->envlst;
	while (current)
	{
		if (!ft_strcmp(key, current->key))
		{
			if (prev)
				prev->next = current->next;
			else
				minishell->envlst = current->next;
			free(current);
			return ;
		}
		prev = current;
		current = current->next;
	}
}

// int	ft_keycheck(char *str)
// {
// 	int	i;

// 	i = 1;
// 	if (!ft_isalpha(*str) && *str != '_')
// 		return (0);
// 	while (str[i] && str[i] != '=')
// 	{
// 		if (!ft_alphanum(str[i]) && str[i] != '_')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

int	ft_unset(char **args, t_minishell *minishell)
{
	int		i;
	bool	err;
	

	i = 1;
	if (!args[1])
		return (0);
	err = false;
	while (args[i])
	{
		if (!ft_keycheck(args[i]))
		{
			ft_putstr_fd("lumumbash: unset: `", 2);
			ft_putstr_fd(args[i], 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			err = true;
		}
		else
			ft_unset_helper(minishell,
				collector(ft_extract_key(args[i]), false));
		i++;
	}
	return (err);
}