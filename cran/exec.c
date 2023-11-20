#include "header.h"
#include "minishell.h"
#include "tokenizer.h"
#include "parser.h"


// helpers
// void	ft_putchar_fd(char c, int fd)
// {
// 	write(fd, &c, 1);
// }
// void	ft_putstr_fd(char *s, int fd)
// {
// 	if (s)
// 		while (*s)
// 			ft_putchar_fd(*s++, fd);
// }
void	ft_putnbr_fd(int n, int fd)
{
	long int	num;

	num = n;
	if (num < 0)
	{
		ft_putchar_fd('-', fd);
		num *= -1;
	}
	if (num < 10)
		ft_putchar_fd(num + '0', fd);
	else
	{
		ft_putnbr_fd(num / 10, fd);
		ft_putchar_fd(num % 10 + '0', fd);
	}
}
void	clear_list(t_list **list, void (*del)(void *))
{
	t_list	*next;
	t_list	*current;

	if (!list || !*list || !del)
		return ;
	current = *list;
	next = current -> next;
	while (current && next)
	{
		del(current -> content);
		free(current);
		current = next;
		next = current -> next;
	}
	del(current -> content);
	free(current);
	*list = NULL;
}

void	list_add(t_list **list, t_list *new)
{	
	t_list	*current_node;

	if (!*list)
	{
		*list = new;
		return ;
	}
	current_node = *list;
	while (current_node && current_node -> next)
		current_node = current_node -> next;
	current_node -> next = new;
}

t_list	*new_in_list(void *content)
{
	t_list	*new_node;

	new_node = calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}






static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*to_trash(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		clear_list(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		list_add(&garbage_list, new_in_list(ptr));
		return (ptr);
	}
}

// runs commands in parallel eg. cmd ; cmd & also for redir
bool	in_parallel(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}

void	clean_shell(t_minishell *minishell)
{
	to_trash(NULL, true);
	clear_ast(&(minishell->ast), &(minishell->tokens));
	clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->original_term));
}



int	get_exit_status(int status)
{
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

// build with other builtins
int	exec_builtin(char **args)
{
	if (strcmp(args[0], "echo") == 0)
		return ft_echo(args);
	if (strcmp(args[0], "pwd") == 0)
		return ft_pwd();
	return CMD_NOT_FOUND;
}

// build with other builtins
bool	ft_is_builtin(char *arg)
{
	if (!arg)
		return (false);
	if (!strcmp(arg, "echo") || !strcmp(arg, "pwd"))
		return (true);
	return (false);
}





// has write permission?
t_error	check_write(char *file)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, W_OK) == -1)
			return ((t_error){GENERAL, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}

int	error_msg(t_error error)
{
	if (error_msg(error) == CMD_NOT_FOUND)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": command not found\n", 2), error.no);
	else if (error_msg(error) == NO_SUCH_FILE)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": No such file or directory\n", 2), error.no);
	else if (error_msg(error) == PERMISSION_DENIED)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": Permission denied\n", 2), error.no);
	else if (error_msg(error) == AMBIGUOUS)
		return (ft_putstr_fd("minishell: ", 2), ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": ambiguous redirect\n", 2), error.no);
	else if (error_msg(error) == TOO_MANY_ARGS)
		return (ft_putstr_fd("minishell: exit: too many arguments\n", 2),
			error.no);
	else if (error_msg(error) == NUMERIC_REQUIRED)
		return (ft_putstr_fd("minishell: exit: ", 2),
			ft_putstr_fd(error.cause, 2),
			ft_putstr_fd(": numeric argument required\n", 2), error.no);
	return (0);
}
// has exec permission?
t_error	check_exec(char *file, bool cmd)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, X_OK) == -1)
			return ((t_error){CANT_EXECUTE, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	if (cmd)
		return ((t_error){NOT_FOUND, CMD_NOT_FOUND, file});
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}
// has read permission?
t_error	check_read(char *file)
{
	if (!*file)
		return ((t_error){GENERAL, NO_SUCH_FILE, file});
	if (access(file, F_OK) == 0)
	{
		if (access(file, R_OK) == -1)
			return ((t_error){GENERAL, PERMISSION_DENIED, file});
		return ((t_error){SUCCESS, 42, NULL});
	}
	return ((t_error){NOT_FOUND, NO_SUCH_FILE, file});
}




// redir output
int	ft_out(t_redir_node *redir_list, int *status)
{
	int		fd;

	if (!redir_list->expanded_value || redir_list->expanded_value[1])
	{
		*status = error_msg(
				(t_error){GENERAL, AMBIGUOUS, redir_list->value});
		return (*status);
	}
	fd = open(redir_list->expanded_value[0], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd == -1)
	{
		*status = error_msg(check_write(redir_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}
// redir in
int	ft_in(t_redir_node *redir_list, int *status)
{
	int		fd;

	if (!redir_list->expanded_value || redir_list->expanded_value[1])
	{
		*status = error_msg(
				(t_error){GENERAL, AMBIGUOUS, redir_list->value});
		return (*status);
	}
	fd = open(redir_list->expanded_value[0], O_RDONLY);
	if (fd == -1)
	{
		*status = error_msg(check_read(redir_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDIN_FILENO);
	close(fd);
	*status = 0;
	return (*status);
}
// append redir
int	ft_append(t_redir_node *redir_list, int *status)
{
	int	fd;

	if (!redir_list->expanded_value || redir_list->expanded_value[1])
	{
		*status = error_msg(
				(t_error){GENERAL, AMBIGUOUS, redir_list->value});
		return (*status);
	}
	fd = open(redir_list->expanded_value[0], O_CREAT | O_WRONLY | O_APPEND, 0644);
	if (fd == -1)
	{
		*status = error_msg(check_write(redir_list->expanded_value[0]));
		return (*status);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
	*status = 0;
	return (0);
}
// cmd has redir
int	check_redir(t_node *node)
{
	t_redir_node	*tmp_redir;
	int			tmp_status;

	tmp_redir = node->redir_list;
	while (tmp_redir)
	{
		if (tmp_redir->type == REDIR_OUT
			&& ft_out(tmp_redir, &tmp_status) != SUCCESS)
			return (tmp_status);
		else if (tmp_redir->type == REDIR_IN
			&& ft_in(tmp_redir, &tmp_status) != SUCCESS)
			return (tmp_status);
		else if (tmp_redir->type == REDIR_APPEND
			&& ft_append(tmp_redir, &tmp_status) != SUCCESS)
			return (tmp_status);
		else if (tmp_redir->type == REDIR_HEREDOC)
			(dup2(tmp_redir->here_doc, 0), close(tmp_redir->here_doc));
		tmp_redir = tmp_redir->next;
	}
	return (SUCCESS);
}

//  reset  standard input and output fds
void	reset_stds(bool piped)
{
	if (piped)
		return ;
	dup2(STDIN_FILENO, 0);
	dup2(STDIN_FILENO, 1);
}


static int	heredoc_expand_writer(char *str, size_t i, int fd, int exit_status)
{
	size_t	start;
	char	*tmp;

	start = ++i;
	if (str[i] == '?')
		return (ft_putnbr_fd(exit_status, fd), 2);
	while (str[i] && str[i] != '$' && str[i] != ' ')
		i++;
	if (i != start)
	{
		tmp = to_trash(ft_substr(str, start, i), false);
		if (tmp)
			ft_putstr_fd(tmp, fd);
	}
	return (i);
}

void	heredoc_expander(char *str, int fd, int exit_status)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			i += heredoc_expand_writer(str, i, fd, exit_status);
		else
			i += (ft_putchar_fd(str[i], fd), 1);
	}
	ft_putchar_fd('\n', fd);
}


bool	is_delimiter(char *delimiter, char *str)
{
	while (*str)
	{
		if (*delimiter == '"' || *delimiter == '\'')
		{
			delimiter++;
			continue ;
		}
		else if (*str == *delimiter)
		{
			str++;
			delimiter++;
		}
		else
			return (false);
	}
	while (*delimiter == '"' || *delimiter == '\'')
		delimiter++;
	return (!*delimiter);
}



void	ft_heredoc(t_redir_node *redir, int p[2], t_minishell *minishell)
{
	char	*line;
	char	*quotes;

	quotes = redir->value;
	while (*quotes && *quotes != '"' && *quotes != '\'')
		quotes++;
	while (1)
	{
		line = readline("> ");
		if (!line)
			break ;
		if (is_delimiter(redir->value, line))
			break ;
		if (!*quotes)
			heredoc_expander(line, p[1], minishell->exit_s);
		else
		{
			ft_putstr_fd(line, p[1]);
			ft_putstr_fd("\n", p[1]);
		}
	}
	clean_shell(minishell);
	exit(minishell->exit_s);
    // exit 0;
}


static bool ft_leave_leaf(int p[2], int *pid) 
{
    waitpid(*pid, NULL, 0);

    close(p[1]);

    return false;
}


static void	ft_init_leaf(t_node *node, t_minishell *minishell)
{
	t_redir_node	*redir;
	int			p[2];
	int			pid;

	redir = node->redir_list;
	while (redir)
	{
		if (redir->type == REDIR_HEREDOC)
		{
			pipe(p);
			pid = fork();
            if (pid == -1)
			{
				perror("Fork error");
				exit(EXIT_FAILURE);
			}
			if (!pid)
				ft_heredoc(redir, p, minishell);
			if (ft_leave_leaf(p, &pid))
				return ;
			redir->here_doc = p[0];
		}
		else
			{
				close(p[1]);  // Close writing end in parent
				redir->here_doc = p[0];  // Store reading end in redir->here_doc
				waitpid(pid, NULL, 0);  // Wait for the child process to finish
			}
		redir = redir->next;
	}
}

void	ft_init_tree(t_node *node, t_minishell *minishell)
{
	if (!node)
		return ;
	if (node->type == NODE_PIPE)
	{
		ft_init_tree(node ->left, minishell);
        ft_init_tree(node ->right, minishell);
	}
	else
		ft_init_leaf(node, minishell);
}



static int	exec_child(t_node *node, t_minishell *minishell)
{
	int		tmp_status;
	int		fork_pid;

	fork_pid = fork();
    if (fork_pid == -1) {
        perror("fork");
        return GENERAL;
    }
	if (!fork_pid)
	{
		tmp_status = check_redir(node);
		if (tmp_status != SUCCESS)
			(clean_shell(minishell), exit(GENERAL));
	}
    else {
        waitpid(fork_pid, &tmp_status, 0);
	    return (get_exit_status(tmp_status));
    }

    return 0;
	
}

int	exec_simple_cmd(t_node *node, bool piped, t_minishell *minishell)
{
	int		tmp_status;

	if (!node || !node->args)
	{
		tmp_status = check_redir(node);
		return (reset_stds(piped), (tmp_status && GENERAL));
	}
	else if (ft_is_builtin(node->args))
	{
		tmp_status = check_redir(node);
		if (tmp_status != SUCCESS)
			return (reset_stds(piped), GENERAL);
		tmp_status = exec_builtin(&(node->args));
		return (reset_stds(piped), tmp_status);
	}
	else
		return exec_child(node, minishell);
}


static	int	exec_pipeline(t_node *tree, t_minishell *minishell)
{
	int	status;
	int	pfds[2];
	int	pid_l;
	int	pid_r;

	pipe(pfds);
	pid_l = fork();
	if (!pid_l)
		exec_pipe_child(tree->left, pfds, TD_LEFT, minishell);
	else
	{
		pid_r = fork();
		if (!pid_r)
			exec_pipe_child(tree->right, pfds, TD_RIGHT, minishell);
		else
		{
			(close(pfds[0]), close(pfds[1]),
				waitpid(pid_l, &status, 0), waitpid(pid_r, &status, 0));
			return (get_exit_status(status));
		}
	}
	return (GENERAL);
}


int	exec_node(t_node *tree, bool piped, t_minishell *minishell)
{
	int	status;

	if (!tree)
		return (1);
	if (tree->type == NODE_PIPE)
		return (exec_pipeline(tree, minishell));
	else
		return (exec_simple_cmd(tree, piped, minishell));
	// return (GENERAL);
}

static void exec_pipe_child(t_node *node, int pfds[2], t_ast_direction direction, t_minishell *minishell)
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
	status = exec_node(node, true, minishell);
	(clean_shell(minishell), exit(status));
}


