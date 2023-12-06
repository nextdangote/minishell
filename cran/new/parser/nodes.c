#include "lumumbash.h"


t_node_type	get_node_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (NODE_PIPE);
	return NODE_UNKNOWN;
}

t_redir_type	get_redir_type(t_token_type type)
{
	if (type == TOKEN_INPUT_REDIRECTION)
		return (REDIR_IN);
	if (type == TOKEN_OUTPUT_REDIRECTION)
		return (REDIR_OUT);
	if (type == TOKEN_HEREDOC)
		return (REDIR_HEREDOC);
	return (REDIR_APPEND);
}

t_node	*new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

t_redir_node	*new_redir_node(t_token_type type, char *value)
{
	t_redir_node	*new_node;

	new_node = (t_redir_node *)calloc(1, sizeof(t_redir_node));
	if (!new_node)
		return (NULL);
	new_node->type = get_redir_type(type);
	new_node->value = strdup(value);
	if (!new_node->value)
		return (free(new_node), NULL);
	return (new_node);
}

void	append_redir_node(t_redir_node **list, t_redir_node *new)
{
	t_redir_node	*current_node;

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

