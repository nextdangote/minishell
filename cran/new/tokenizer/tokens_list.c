#include "lumumbash.h"


void	clear_token_list(t_token **list)
{
	t_token	*current_node;
	t_token	*next;

	current_node = *list;


	while (current_node)
	{
		next = current_node->next;

		if (current_node->value)
		{
			free(current_node->value);
            current_node->value = NULL;
        }
		free(current_node);
		current_node = next;
	}
	*list = NULL;
}



void	token_list_add_back(t_token **lst, t_token *new_token)
{
	t_token	*curr_node;

	if (!*lst)
	{
		*lst = new_token;
		return ;
	}
	curr_node = *lst;
	while (curr_node && curr_node -> next)
		curr_node = curr_node -> next;
	curr_node -> next = new_token;
	new_token -> prev = curr_node;
}