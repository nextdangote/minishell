
#include "lumumbash.h"


// CHECK THE CODE FOR THESE FUNCTIONS
// ft_update_envlst -ok
// ft_get_envlst_val -ok
// ft_putstr_fd
// chdir
//ft_strcmp
//ft_envlst_back -ok
//ft_envlst_new 
//ft_strdup

void	ft_envlst_back(t_env *new)
{
	t_env	*curr;
    t_minishell *minishell;

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

void	ft_update_envlst(char *key, char *value, bool create)
{
	t_env	*envlst;
    t_minishell *minishell;

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
		ft_envlst_back(ft_envlst_new(key, value));
}

char	*ft_get_envlst_val(char *key)
{
	t_env	*envlst;
    t_minishell *minishell;

	envlst = minishell->envlst;
	while (envlst)
	{
		if (!ft_strcmp(key, envlst->key))
			return (envlst->value);
		envlst = envlst->next;
	}
	return (NULL);
}

static int	ft_change_pwd(void)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (1);
	return (ft_update_envlst("PWD", cwd, false), 0);
}


static int	ft_cd_home(void)
{
	char	*home;

	ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
	home = ft_get_envlst_val("HOME");
	if (!home)
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (chdir(home) == SUCCESS)
		return (ft_update_envlst("PWD", home, false), 0);
	return (1);
}

static int	ft_cd_err_msg(char *err_msg)
{
	ft_putstr_fd("minishell: cd: `", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("': No such file or directory\n", 2);
	return (1);
}

int	ft_cd(char *path)
{
	if (!path)
		return (ft_cd_home());
	if (chdir(path) != SUCCESS)
		return (ft_cd_err_msg(path));
	ft_update_envlst("OLDPWD", ft_get_envlst_val("PWD"), false);
	return (ft_change_pwd());
}