#include "lumumbash.h"




// int exec_child(t_node *node) {
//     int tmp_status;
//     int fork_pid;
//     t_minishell *t_minishell;

//     fork_pid = fork();
//     if (!fork_pid) 
//     {
//         tmp_status = check_redir(node);
//         // if (tmp_status != SUCCESS) {
//         //     // clean_shell(t_minishell);
//         //     exit(GENERAL);
//         // }
//         // execvp(node->split_args[0], node->split_args);
//         printf("exec_child: Executing command - %s\n", node->split_args[0]);
// for (int i = 0; node->split_args[i] != NULL; i++) {
//     printf("exec_child: Argument %d - %s\n", i, node->split_args[i]);
// }
// execvp(node->split_args[0], node->split_args);
//         // If execvp fails, exit with an error code
//         perror("execvp");
//         exit(EXIT_FAILURE);

//     }
//     waitpid(fork_pid, &tmp_status, 0);
//     return get_exit_status(tmp_status);
// }


// before expander below
int exec_child(t_node *node) {
    int tmp_status;
    pid_t pid;

    pid = fork();
    if (pid == 0) 
    {
        // Child process
        if (execvp(node->split_args[0], node->split_args) == -1) {
            perror("lsh");
        }
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        // Error forking
        perror("lsh");
    } else {
        // Parent process
        do {
            waitpid(pid, &tmp_status, WUNTRACED);
        } while (!WIFEXITED(tmp_status) && !WIFSIGNALED(tmp_status));
    }

    return 1;
}







// static int exec_child(t_node *node, t_minishell *minishell)
// {
//     int tmp_status;
//     int fork_pid;

//     fork_pid = fork();

//     // if (fork_pid == -1)
//     // {
//     //     perror("fork");
//     //     return EXIT_FAILURE;
//     // }

//     if (!fork_pid)
//     {
//         tmp_status = check_redir(node);
//         if (tmp_status != SUCCESS)
//         {
//             clean_shell(minishell);
//             // exit(EXIT_FAILURE);
//             exit(GENERAL);

//         }

//         if (execve((node->args)[0], node->args, NULL) == -1)
//         {
//             perror("minishell");
//             exit(EXIT_FAILURE);
//         }
//     }
//     else
//     {
//         waitpid(fork_pid, &tmp_status, 0);
//         return get_exit_status(tmp_status);
//     }

//     return EXIT_FAILURE;
// }
        // if (execve(node->args[0], node->args, NULL) == -1) {
        //     clean_shell(t_minishell);
        //     exit(1);
        // }