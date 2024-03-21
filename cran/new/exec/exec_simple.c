#include "lumumbash.h"


void	reset_stds(bool piped)
{
	if (piped)
		return ;
	dup2(STDIN_FILENO, 0);
	dup2(STDOUT_FILENO, 1);
}


// int	exec_builtin(char **args)
// {
// 	printf("exec_builtin: Executing command - %s\n", args[0]);

// 	if (strcmp(args[0], "echo") == 0)
// 		return (ft_echo(args));
// 		printf("exec_builtin: Echo logic\n");
// 	if (strcmp(args[0], "pwd") == 0)
// 		return (ft_pwd());
// 	ft_exit(args);
// 	return (GENERAL);
// }


// int	exec_builtin(char **args)
// {
//     printf("exec_builtin: Executing command - %s\n", args[0]);

//     if (strcmp(args[0], "echo") == 0)
//     {
//         printf("exec_builtin: Echo logic\n");
//         return (ft_echo(args));
//     }
//     if (strcmp(args[0], "pwd") == 0)
//     {
//         return (ft_pwd());
//     }
//     if (strcmp(args[0], "exit") == 0)
//     {
//         ft_exit(args);
//         return (GENERAL);
//     }
//     return (GENERAL);
// }



// added minishell as argument on march 22, to fit the new ft_exit

// int exec_builtin(char **args, t_minishell *minishell)
// {
//     printf("exec_builtin: Executing command - %s\n", args[0]);
//     if (!strcmp(args[0], "echo"))
//     {
//         printf("exec_builtin: Echo logic\n");
//         return ft_echo(args + 1);
//     }
//     else if (!strcmp(args[0], "exit"))
//     {
//         ft_exit(args, minishell);
//          return (GENERAL);
//         // printf("exec_builtin: Exit logic\n");
//         // return ft_exit(args + 1);  
//     }
//     else if (!strcmp(args[0], "pwd"))
//     {
//         return (ft_pwd());
//         // printf("exec_builtin: PWD logic\n");
//         // return ft_pwd(args + 1);  
//     }
//     else
//     {
//         printf("exec_builtin: Command not recognized\n");
//         return GENERAL;
//     }
// }


int	exec_builtin(char **args, t_minishell *minishell)
{
    printf("exec_builtin: Executing command - %s\n", args[0]);
	if (!ft_strcmp(args[0], "echo"))
		return (ft_echo(args + 1));
	// if (!ft_strcmp(args[0], "cd"))
	// 	return (ft_cd(args[1]));
	if (!ft_strcmp(args[0], "env"))
		return (ft_env(minishell));
	if (!ft_strcmp(args[0], "pwd"))
		return (ft_pwd());
	if (!ft_strcmp(args[0], "export"))
		return (ft_export(args, minishell));
	if (!ft_strcmp(args[0], "unset"))
		return (ft_unset(args, minishell));
	ft_exit(args, minishell);
	return (GENERAL);
}



bool is_builtin(char *arg)
{
    if (!arg)
	{
        return false;
		// printf("is_builtin: Checking command - %s\n", arg);
	}
    printf("is_builtin: Checking command - %s\n", arg);

    if (!strcmp(arg, "echo") || !strcmp(arg, "exit") || !strcmp(arg, "pwd") || !strcmp(arg, "export") || !strcmp(arg, "unset") || !strcmp(arg, "env") || !strcmp(arg, "cd"))
	{
		printf("is_builtin: Detected as builtin command\n");
        return true;
	}
	printf("is_builtin: Not a builtin command\n");
    return false;
}

// bool is_builtin(char *arg)
// {
//     printf("is_builtin: Checking command - %s\n", arg);
//     if (!arg)
//     {
//         return false;
//     }
//     if (!strcmp(arg, "echo") || !strcmp(arg, "exit") || !strcmp(arg, "pwd"))
//     {
//         printf("is_builtin: Detected as builtin command\n");
//         return true;
//     }
//     printf("is_builtin: Not a builtin command\n");
//     return false;
// }


// int exec_simple_cmd(t_node *node, bool piped)
// {
//     int tmp_status;

// 	if (node->args == NULL) {
//         return 0;
//     }

// 	if (!node->split_args) 
// 	{
// 		tmp_status = check_redir(node);
// 		return (reset_stds(piped), (tmp_status && GENERAL));
// 	}
//     else if (is_builtin((node->split_args)[0]))
//     {
//         printf("exec_simple_cmd: Detected builtin command\n");

//         tmp_status = check_redir(node);
//         if (tmp_status != SUCCESS)
//         {
//             reset_stds(piped);
//             printf("exec_simple_cmd: Redirection check failed\n");
//             return GENERAL;
//         }

// 		tmp_status = exec_builtin(node -> split_args);
// 		return (reset_stds(piped), tmp_status);
//     }
//     else
//     {
//         printf("exec_simple_cmd: Not a builtin command\n");
//         return exec_child(node);
//     }
    
// }






// int exec_simple_cmd(t_node *node, bool piped)
// {
//     int tmp_status;

//     if (node->args == NULL) {
//         return 0;
//     }

//     else if (is_builtin(&node->args[0]))
//         // else if (is_builtin((node->args)[0]))

//     {
//         printf("exec_simple_cmd: Detected builtin command\n");

//         tmp_status = check_redir(node);
//         if (tmp_status != SUCCESS)
//         {
//             reset_stds(piped);
//             printf("exec_simple_cmd: Redirection check failed\n");
//             return GENERAL;
//         }

//         tmp_status = exec_builtin(&node->args);
//                 // tmp_status = exec_builtin(node->args);

//         return (reset_stds(piped), tmp_status);
//     }
//     else
//     {
//         printf("exec_simple_cmd: Not a builtin command\n");
//         return exec_child(node);
//     }
// }



int exec_simple_cmd(t_node *node, bool piped, t_minishell *minishell)
{
    int tmp_status;
    if (node->args == NULL) {
        return 0;
    }

    // Split the command into separate words
    char **split_args = malloc(MAX_NUM_ARGS * sizeof(char *) + 1);
    char *arg = strtok(node->args, " ");
    int i = 0;
    while (arg != NULL) {
        split_args[i] = arg;
        i++;
        arg = strtok(NULL, " ");
    }
    split_args[i] = NULL;  

    if (is_builtin(split_args[0]))
    {
        printf("exec_simple_cmd: Detected builtin command\n");
        tmp_status = check_redir(node);
        if (tmp_status != SUCCESS)
        {
            reset_stds(piped);
            printf("exec_simple_cmd: Redirection check failed\n");
            return GENERAL;
        }
        tmp_status = exec_builtin(split_args, minishell);
        free(split_args);  
        return (reset_stds(piped), tmp_status);
    }
    else
    {
        printf("exec_simple_cmd: Not a builtin command\n");
        free(split_args);  
        return exec_child(node);
    }
}



// int	exec_builtin(char **args)
// {
// 	if (strcmp(args[0], "echo") == 0)
// 		return (ft_echo(args));
// 	if (strcmp(args[0], "pwd") == 0)
// 		return (ft_pwd());
// 	ft_exit(args);
// 	return (GENERAL);
// }
// int	exec_simple_cmd(t_node *node, bool piped)
// {
// 	int tmp_status;
	
// 	if (is_builtin((node->args)))
// 	{
// 		tmp_status = check_redir(node);
// 		if (tmp_status != SUCCESS)
// 			return (reset_stds(piped), GENERAL);
// 		tmp_status = exec_builtin(&(node->args));
// 		return (reset_stds(piped), tmp_status);
// 	}
// 	else
// 		return exec_child(node);
// }



// int	exec_simple_cmd(t_node *node, bool piped)
// {
// 	int tmp_status;
	
// 	if (is_builtin(&(node->args)))
// 	{
// 		tmp_status = check_redir(node);
// 		if (tmp_status != SUCCESS)
// 			return (reset_stds(piped), GENERAL);
// 		tmp_status = exec_builtin(&(node->args[0]), (&node->args));
// 		return (reset_stds(piped), tmp_status);
// 	}
// 	else
// 		return exec_child(node);
// }


// int exec_simple_cmd(t_node *node, bool piped)
// {
//     int tmp_status;

//     if (is_builtin(&(node->args[0])))
//     {
//         tmp_status = check_redir(node);
//         if (tmp_status != SUCCESS)
//         {
//             reset_stds(piped);
//             return GENERAL;
//         }

//         reset_stds(piped);
//         return exec_builtin(&(node->args[0]), (&node->args));
//     }
//     else
//     {
//         return exec_child(node);
//     }
// }
// split_args = expanded args?
