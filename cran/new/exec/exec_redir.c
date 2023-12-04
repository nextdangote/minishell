#include "lumumbash.h"


int ft_out(t_redir_node *redir_list, int *status)
{
    int fd;

    if (!redir_list->value || redir_list->value[1])
    {
        *status = error_msg((t_error){GENERAL, AMBIGUOUS, redir_list->value});
        return *status;
    }
    fd = open(&redir_list->value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1)
    {
        *status = error_msg(ft_check_write(&redir_list->value[0]));
        return *status;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    *status = 0;
    return *status;
}



int ft_in(t_redir_node *redir_list, int *status)
{
    int fd;

    if (!redir_list->value || redir_list->value[1])
    {
        *status = error_msg((t_error){GENERAL, AMBIGUOUS, redir_list->value});
        return *status;
    }
    fd = open(&redir_list->value[0], O_RDONLY);
    if (fd == -1)
    {
        *status = error_msg(ft_check_read(&redir_list->value[0]));
        return *status;
    }
    dup2(fd, STDIN_FILENO);
    close(fd);
    *status = 0;
    return *status;
}

int ft_append(t_redir_node *redir_list, int *status)
{
    int fd;

    if (!redir_list->value || redir_list->value[1])
    {
        *status = error_msg((t_error){GENERAL, AMBIGUOUS, redir_list->value});
        return *status;
    }
    fd = open(&redir_list->value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1)
    {
        *status = error_msg(ft_check_write(&redir_list->value[0]));
        return *status;
    }
    dup2(fd, STDOUT_FILENO);
    close(fd);
    *status = 0;
    return *status;
}
