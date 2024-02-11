#include "lumumbash.h"


// static int check_flag(char *arg)
// {
//     if (arg[0] != '-' || strcmp(arg, "-n") == 0)
//         return 0;
//     int i = 1;
//     while (arg[i] != '\0') {
//         if (arg[i] != 'n')
//             return 0;
//         i++;
//     }
//     return 1;
// }

// int	ft_echo(char **args)
// {
// 	int	i;
// 	int	flag;

// 	i = 1;
// 	flag = 0;
// 	while (args[i] != NULL && check_flag(args[i]) == 1)
// 	{
// 		flag = 1;
// 		i++;
// 	}
// 	while (args[i])
// 	{
// 		ft_putstr_fd(args[i], 1);
// 		if (args[i + 1])
// 			ft_putstr_fd(" ", 1);
// 		i++;
// 	}
// 	if (flag == 0)
// 		ft_putstr_fd("\n", 1);
// 	return (0);
// }



/// new added


static int check_flag(char *arg)
{
	int	i;

	i = 0;
	if (arg[0] != '-')
		return (0);
	i++;
	while (arg[i])
	{
		if (arg[i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

// int	ft_echo(char **args)
// {
// 	int	i;
// 	int	opt;

// 	i = 1;
// 	opt = 0;
// 	while (args[i] != NULL && check_flag(args[i]) == 1)
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

//added after expander
// int	ft_echo(char **args)
// {
//     int	i;

//     i = 0;
//     while (args[i])
//     {
//         char *arg = args[i];
//         size_t len = strlen(arg);
//         if ((arg[0] == '"' || arg[0] == '\'') && arg[0] == arg[len - 1]) {
//             // If the argument starts and ends with a quote, remove the quotes
//             arg[len - 1] = '\0';
//             arg++;
//         }
//         ft_putstr_fd(arg, 1);
//         if (args[i + 1])
//             ft_putstr_fd(" ", 1);
//         i++;
//     }
//     ft_putstr_fd("\n", 1);
//     return (0);
// }




int	ft_echo(char **args)
{
    int	i;
    int	newline;

    i = 0;
    newline = 1;
    while (args[i] && check_flag(args[i]))
    {
        newline = 0;
        i++;
    }
    while (args[i])
    {
        char *arg = args[i];
        size_t len = strlen(arg);
        // If the argument starts with a backslash, skip it
        if (arg[0] == '\\') {
            arg++;
            len--;
        }
        if ((arg[0] == '"' || arg[0] == '\'') && arg[0] == arg[len - 1]) {
            // If the argument starts and ends with a quote, remove the quotes
            arg[len - 1] = '\0';
            arg++;
        }
        ft_putstr_fd(arg, 1);
        if (args[i + 1])
            ft_putstr_fd(" ", 1);
        i++;
    }
    if (newline)
        ft_putstr_fd("\n", 1);
    return (0);
}
