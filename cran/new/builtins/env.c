#include "lumumbash.h"


void	ft_init_envlst(t_minishell *minishell)
{
	int		i;
	char	**environ;
	char	*key;
	char	*value;
    

	environ = minishell->environ;
	if (!environ)
		return ;
	i = 0;
	while (environ[i])
	{
		key = ft_extract_key(environ[i]);
		value = ft_extract_value(environ[i]);
		ft_update_envlst(key, value, true, minishell);
		i++;
	}
}

int	ft_env(t_minishell *minishell)
{
	t_env	*list;
    // t_minishell *minishell;

    list = minishell->envlst;
	while (list)
	{
		if (list->value != NULL)
			printf("%s=%s\n", list->key, list->value);
		list = list->next;
	}
	return (SUCCESS);
}
