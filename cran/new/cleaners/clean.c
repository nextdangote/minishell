#include "lumumbash.h"



void	ft_lstclear(t_list **lst, void (*del)(void *))
{
	t_list	*next;
	t_list	*curr;

	if (!lst || !*lst || !del)
		return ;
	curr = *lst;
	next = curr -> next;
	while (curr && next)
	{
		del(curr -> content);
		free(curr);
		curr = next;
		next = curr -> next;
	}
	del(curr -> content);
	free(curr);
	*lst = NULL;
}


// void	clean_shell(t_minishell *minishell)
// {
// 	to_trash(NULL, true);
// 	clear_ast(&(minishell->ast), &(minishell->tokens));
// 	clear_history();
// 	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->original_term));
// }


void	clean_shell(t_minishell *minishell)
{
	collector(NULL, true);
	ft_clear_ast(&(minishell->ast), minishell);
	clear_history();
	tcsetattr(STDIN_FILENO, TCSANOW, &(minishell->original_term));
}


static void	ft_del(void *ptr)
{
	free(ptr);
	ptr = NULL;
}

void	*collector(void *ptr, bool clean)
{
	static t_list	*garbage_list;

	if (clean)
	{
		ft_lstclear(&garbage_list, ft_del);
		return (NULL);
	}
	else
	{
		ft_lstadd_back(&garbage_list, ft_lstnew(ptr));
		return (ptr);
	}
}