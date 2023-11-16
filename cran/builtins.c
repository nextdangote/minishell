#include "tokenizer.h"
#include "minishell.h"
#include "parser.h"
#include "header.h"


// pwd

int	ft_pwd(void)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (!cwd)
		return (1);
	ft_putstr_fd(cwd, 1);
	ft_putstr_fd("\n", 1);
	return (0);
}


// echo

// static int	ft_check_flag(char *s)
// {
// 	int	i;

// 	i = 0;
// 	if (s[0] != '-')
// 		return (0);
// 	i++;
// 	while (s[i])
// 	{
// 		if (s[i] != 'n')
// 			return (0);
// 		i++;
// 	}
// 	return (1);
// }

// // static int ft_check_option(char *s) {
// //     return (s && strcmp(s, "-n") == 0);
// // }

// int	ft_echo(char **args)
// {
// 	int	i;
// 	int	opt;

// 	i = 1;
// 	opt = 0;
// 	while (args[i] != NULL && ft_check_flag(args[i]) == 1)
// 	{
// 		opt = 1;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		ft_putstr_fd(args[i], 1);
// 		if (args[i + 1])
// 			ft_putstr_fd(" ", 1);
// 		i++;
// 	}
// 	if (opt == 0)
// 		ft_putstr_fd("\n", 1);
// 	return (0);
// }


static bool	ft_check_flag(char *arg)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 0;
	if (arg[i] != '-')
		return (n_flag);
	i++;
	while (arg[i] && arg[i] == 'n')
		i++;
	if (arg[i] == '\0')
		n_flag = true;
	return (n_flag);
}

static void	echo_print_args(char **args, bool n_flag, int i)
{
	if (!args[i])
	{
		if (!n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		return ;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putchar_fd(' ', STDOUT_FILENO);
		else if (!args[i + 1] && !n_flag)
			ft_putchar_fd('\n', STDOUT_FILENO);
		i++;
	}
}

int	ft_echo(char **args)
{
	int		i;
	bool	n_flag;

	n_flag = false;
	i = 1;
	while (args[i] && ft_check_flag(args[i]))
	{
		n_flag = true;
		i++;
	}
	echo_print_args(args, n_flag, i);
	return (EXIT_SUCCESS);
}