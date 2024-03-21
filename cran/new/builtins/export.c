#include "lumumbash.h"

static int	ft_export_error_msg(char *identifier)
{
	ft_putstr_fd("lumumbash: export: `", 2);
	ft_putstr_fd(identifier, 2);
	ft_putstr_fd("': not a valid identifier\n", 2);
	return (1);
}

static	void	ft_export_list(t_minishell *minishell)
{
	t_env	*list;
	size_t	i;


	list = minishell->envlst;
	while (list)
	{
		if (list->value != NULL && (ft_strcmp(list->key, "_") != 0))
		{
			printf("declare -x %s=\"", list->key);
			i = 0;
			while ((list->value)[i])
			{
				if ((list->value)[i] == '$' || (list->value)[i] == '"')
					printf("\\%c", (list->value)[i++]);
				else
					printf("%c", (list->value)[i++]);
			}
			printf("\"\n");
		}
		else if (list->value == NULL && (ft_strcmp(list->key, "_") != 0))
			printf("declare -x %s\n", list->key);
		list = list->next;
	}
}

static t_env	*ft_envlst_new(char *key, char *value)
{
	t_env	*new;

	new = (t_env *)ft_calloc(1, sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = collector(ft_strdup(key), false);
	if (value)
		new->value = collector(ft_strdup(value), false);
	new->next = NULL;
	return (new);
}


void	ft_update_envlst(char *key, char *value, bool create, t_minishell *minishell)
{
	t_env	*envlst;
	

	envlst = minishell->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
		{
			if (value)
				envlst->value = collector(ft_strdup(value), false);
			return ;
		}
		envlst = envlst->next;
	}
	if (create)
		ft_envlst_back(ft_envlst_new(key, value), minishell);
}

int	ft_export(char **argv, t_minishell *minishell)
{
	int		i;
	int		exit_s;
	char	*key;

	exit_s = 0;
	i = 1;
	if (!argv[1])
		return (ft_export_list(minishell), 0);
	while (argv[i])
	{
		if (ft_keycheck(argv[i]) == 0)
			exit_s = ft_export_error_msg(argv[i]);
		else
		{
			key = ft_extract_key(argv[i]);
			if (ft_env_entry_exists(key, minishell))
				ft_update_envlst(key, ft_extract_value(argv[i]), false, minishell);
			else
				ft_update_envlst(key, ft_extract_value(argv[i]), true, minishell);
		}
		i++;
	}
	return (exit_s);
}
