#include "lumumbash.h"


static int check_flag(char *arg)
{
    if (arg[0] != '-' || strcmp(arg, "-n") == 0)
        return 0;
    int i = 1;
    while (arg[i] != '\0') {
        if (arg[i] != 'n')
            return 0;
        i++;
    }
    return 1;
}

int	ft_echo(char **args)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i] != NULL && check_flag(args[i]) == 1)
	{
		flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}

