#include "lumumbash.h"


void	reset_stds(bool piped)
{
	if (piped)
		return ;
	dup2(STDIN_FILENO, 0);
	dup2(STDIN_FILENO, 1);
}

int	exec_builtin(char **args)
{
	if (strcmp(args[0], "echo") == 0)
		return (ft_echo(args));
	if (strcmp(args[0], "pwd") == 0)
		return (ft_pwd());
	ft_exit(args);
	return (GENERAL);
}

bool	is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!strcmp(arg, "echo") || !strcmp(arg, "exit") || !strcmp(arg, "pwd"))
		return (true);
	return (false);
}


int	exec_simple_cmd(t_node *node, bool piped)
{
	int tmp_status;
	
	if (is_builtin((node->args)[0]))
	{
		tmp_status = check_redir(node);
		if (tmp_status != SUCCESS)
			return (reset_stds(piped), GENERAL);
		tmp_status = exec_builtin(node->args);
		return (reset_stds(piped), tmp_status);
	}
	else
		return exec_child(node);
}