#include "lumumbash.h"

// int	ft_isdigit(int c)
// {
// 	if ((c >= '0' && c <= '9'))
// 		return (1);
// 	return (0);
// }

static bool	ft_isnumber(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (false);
		i++;
	}
	return (true);
}

static void	ft_skip_spaces_and_get_sign(char *s, int *i, int *sign)
{
	while (s[*i] && s[*i] == ' ')
		(*i)++;
	if (s[*i] == '+' || s[*i] == '-')
	{
		if (s[*i] == '-')
			*sign *= -1;
		(*i)++;
	}
}


static int	ft_exittoi(char *s, t_minishell *minishell)
{
	int					i;
	int					sign;
	int					exit_s;
	unsigned long long	result;
	// t_minishell *minishell = NULL;
	i = 0;
	sign = 1;
	ft_skip_spaces_and_get_sign(s, &i, &sign);
	if (!ft_isnumber(s + i))
	{
		exit_s = error_msg((t_error){ERROR_EXEC_255, NUMERIC_REQUIRED, s});
		(clean_shell(minishell), exit(exit_s));
	}
	result = 0;
	while (s[i])
	{
		result = (result * 10) + (s[i] - '0');
		if (result > LONG_MAX)
		{
			exit_s = error_msg((t_error){ERROR_EXEC_255, NUMERIC_REQUIRED, s});
			(clean_shell(minishell), exit(exit_s));
		}
		i++;
	}
	return ((result * sign) % 256);
}

// modified march 20
void	ft_exit(char **args, t_minishell *minishell)
{
	int	exit_s;

	exit_s = minishell->exit_s;
	if (args[1])
	{
		if (args[2] && ft_isnumber(args[1]))
		{
			exit_s = error_msg(
					(t_error){GENERAL, TOO_MANY_ARGS, NULL});
			clean_shell(minishell);
			exit(exit_s);
		}
		else
			exit_s = ft_exittoi(args[1], minishell);
	}
	clean_shell(minishell);
	exit(exit_s);
}
