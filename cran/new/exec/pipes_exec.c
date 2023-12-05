#include "lumumbash.h"



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



int exec_child(t_node *node) {
    int tmp_status;
    int fork_pid;
    t_minishell *t_minishell;

    fork_pid = fork();
    if (!fork_pid) {
        tmp_status = check_redir(node);
        if (tmp_status != SUCCESS) {
            clean_shell(t_minishell);
            exit(GENERAL);
        }
        if (execve(node->args[0], node->args, NULL) == -1) {
            clean_shell(t_minishell);
            exit(1);
        }
    }
    waitpid(fork_pid, &tmp_status, 0);
    return get_exit_status(tmp_status);
}
