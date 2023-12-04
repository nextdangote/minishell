#include "lumumbash.h"


int	error_msg(t_error error)
{
	if (error.msg == CMD_NOT_FOUND)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": command not found\n", 2), error.no);
	else if (error.msg == NO_SUCH_FILE)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": No such file or directory\n", 2), error.no);
	else if (error.msg == PERMISSION_DENIED)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": Permission denied\n", 2), error.no);
	else if (error.msg == AMBIGUOUS)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), error.no);
	else if (error.msg == TOO_MANY_ARGS)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
			error.no);
	else if (error.msg == NUMERIC_REQUIRED)
		return (ft_putstr_fd("minishell: exit: ", 2),
			ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": numeric argument required\n", 2), error.no);
	return (0);
}
