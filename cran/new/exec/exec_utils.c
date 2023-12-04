#include "lumumbash.h"




void	ft_lstadd_back(t_list **lst, t_list *new)
{	
	t_list	*curr_node;

	if (!*lst)
	{
		*lst = new;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node -> next)
		curr_node = curr_node -> next;
	curr_node -> next = new;
}

t_list	*ft_lstnew(void *content)
{
	t_list	*new_node;

	new_node = calloc(1, sizeof(t_list));
	if (!new_node)
		return (NULL);
	new_node -> content = content;
	new_node -> next = NULL;
	return (new_node);
}


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


