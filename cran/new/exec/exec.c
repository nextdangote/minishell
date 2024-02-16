#include "lumumbash.h"



int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

static void exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction)
{
    int	status;

    if (direction == TD_LEFT)
    {
        close(pfds[0]);
        dup2(pfds[1], STDOUT_FILENO);
        close(pfds[1]);
    }
    else if (direction == TD_RIGHT)
    {
        close(pfds[1]);
        dup2(pfds[0], STDIN_FILENO);
        close(pfds[0]);
    }
    status = exec_node(node, true);
    // (clean_shell(minishell), 
	exit(status);
}

// static	int	exec_pipeline(t_node *tree)
// {
// 	int	status;
// 	int	pfds[2];
// 	int	pid_left;
// 	int	pid_right;
// 	t_minishell *minishell;

// 	pipe(pfds);
// 	pid_left = fork();
// 	if (!pid_left)
// 		// exec_pipe_child(tree->left, pfds, TD_LEFT);
// 		exec_pipe_child(tree->left, pfds, TD_LEFT, minishell);
// 	else
// 	{
// 		pid_right = fork();
// 		if (!pid_right)
// 			// exec_pipe_child(tree->right, pfds, TD_RIGHT);
// 			exec_pipe_child(tree->right, pfds, TD_RIGHT, minishell);
// 		else
// 		{
// 			(close(pfds[0]), close(pfds[1]), waitpid(pid_left, &status, 0), waitpid(pid_right, &status, 0));
// 			return (get_exit_status(status));
// 		}
// 	}
// 	return (GENERAL);
// }

// static int exec_pipeline(t_node *tree)
// {
//     int status;
//     int pfds[2];
//     int pid_left;
//     int pid_right;

//     pipe(pfds);
//     pid_left = fork();
//     if (!pid_left)
//     {
//         exec_pipe_child(tree->left, pfds, TD_LEFT);
//     }
//     else
//     {
//         pid_right = fork();
//         if (!pid_right)
//         {
//             exec_pipe_child(tree->right, pfds, TD_RIGHT);
//         }
//         else
//         {
//             close(pfds[0]);
//             close(pfds[1]);
            
//             waitpid(pid_left, &status, 0);
//             waitpid(pid_right, &status, 0);
//             return get_exit_status(status);
//         }
//     }
//     return GENERAL;
// }

// static int exec_pipeline(t_node *tree)
// {
//     int status;
//     int pfds[2];
//     int pid_left;
//     int pid_right;

//     pipe(pfds);
//     pid_left = fork();
//     if (pid_left == 0)
//     {
//         close(pfds[0]);
//         dup2(pfds[1], STDOUT_FILENO);
//         close(pfds[1]);
//         exec_node(tree->left, true);
//         exit(EXIT_FAILURE);
//     }

//     pid_right = fork();
//     if (pid_right == 0)
//     {
//         close(pfds[1]);
//         dup2(pfds[0], STDIN_FILENO);
//         close(pfds[0]);
//         exec_node(tree->right, true);
//         exit(EXIT_FAILURE);
//     }

//     close(pfds[0]);
//     close(pfds[1]);
//     waitpid(pid_left, &status, 0);
//     waitpid(pid_right, &status, 0);
//     return get_exit_status(status);
// }

static int exec_pipeline(t_node *tree)
{
	printf("exec_pipeline: Executing piped commands\n");
    int status;
    int pfds[2];
    int pid_left;
    int pid_right;

    pipe(pfds);
    pid_left = fork();
    if (!pid_left)
        exec_pipe_child(tree->left, pfds, TD_LEFT);
    else
    {
        pid_right = fork();
        if (!pid_right)
            exec_pipe_child(tree->right, pfds, TD_RIGHT);
        else
        {
            close(pfds[0]);
            close(pfds[1]);
            waitpid(pid_left, &status, 0);
            waitpid(pid_right, &status, 0);
            return (get_exit_status(status));
        }
    }
    return (GENERAL);
}



int	exec_node(t_node *tree, bool piped)
{
	// int	status;

	if (!tree)
		return (1);
	if (tree->type == NODE_PIPE)
		return (exec_pipeline(tree));
	else
		return (exec_simple_cmd(tree, piped));
	return (GENERAL);
}












// static void exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction)
// {
// 	int	status;
//     t_minishell *t_minishell;

// 	if (direction == TD_LEFT)
// 	{
// 		close(pfds[0]);
// 		dup2(pfds[1], STDOUT_FILENO);
// 		close(pfds[1]);
// 	}
// 	else if (direction == TD_RIGHT)
// 	{
// 		close(pfds[1]);
// 		dup2(pfds[0], STDIN_FILENO);
// 		close(pfds[0]);
// 	}
// 	status = exec_node(node, true);
// 	(clean_shell(t_minishell), exit(status));
// }

// int	exec_node(t_node *tree, bool piped, t_minishell *minishell)
// {
// 	int	status;

// 	if (!tree)
// 		return 1;
// 	if (tree->type == NODE_PIPE)
// 		return (exec_pipeline(tree, minishell));
// 	else
// 		return (exec_simple_cmd(tree, piped, minishell));
// 	return GENERAL;
// }
