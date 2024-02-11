#include "lumumbash.h"


static t_node *get_simple_cmd(t_minishell *minishell) 
{
    t_node *node;
	
	if (minishell->parse_error.type)
        return NULL;
    node = new_node(NODE_CMD);
    if (!node) {
		set_parse_error(MALLOC_ERROR);
		return NULL;
    }
	

    while (minishell->current_token && (minishell->current_token->type == TOKEN_WORD || is_redir(minishell->current_token->type))) {
    
		if (minishell->current_token->type == TOKEN_WORD)
		{
			if (!ft_join_args(&(node->args), minishell))
			{
				ft_clear_cmd_node(node);
				set_parse_error(MALLOC_ERROR);
				return NULL;
			}
		  
        } else if (is_redir(minishell->current_token->type)) {
            if (!get_redir_list(&(node->redir_list), minishell)) {
                free(node->args);
                free(node);
                return NULL;
            }
        }
    }
    return node;
}


// static t_node *get_simple_cmd(t_minishell *minishell) 
// {
//     t_node *node;
    
//     if (minishell->parse_error.type)
//         return NULL;
//     node = new_node(NODE_CMD);
//     if (!node) {
//         set_parse_error(MALLOC_ERROR);
//         return NULL;
//     }
    
//     // If the first token is a redirection operator, create an empty command
//     if (minishell->current_token && is_redir(minishell->current_token->type)) {
//         node->args = NULL;
//     }

//     while (minishell->current_token && (minishell->current_token->type == TOKEN_WORD || is_redir(minishell->current_token->type))) {
    
//         if (minishell->current_token->type == TOKEN_WORD)
//         {
//             if (!ft_join_args(&(node->args), minishell))
//             {
//                 ft_clear_cmd_node(node);
//                 set_parse_error(MALLOC_ERROR);
//                 return NULL;
//             }
          
//         } else if (is_redir(minishell->current_token->type)) {
//             if (!get_redir_list(&(node->redir_list), minishell)) {
//                 free(node->args);
//                 free(node);
//                 return NULL;
//             }
//         }
//     }
//     return node;
// }




t_node	*ft_term(t_minishell *minishell)
{
	t_node	*node;

	if (minishell->parse_error.type)
		return NULL;
	if (current_token_is_op(minishell)) {
		set_parse_error(SYNTAX_ERROR);
        return NULL;
    } else {
		return (get_simple_cmd(minishell));
    }
}


t_node	*ft_combine(t_token_type op, t_node *left, t_node *right, t_minishell *minishell)
{
	t_node	*node;

	if (minishell->parse_error.type)
		return (NULL);
	node = new_node(get_node_type(op));
	if (!node)
		return (set_parse_error(MALLOC_ERROR), NULL);
	node->left = left;
	node->right = right;
	return (node);
}


t_node	*ft_expression(t_minishell *minishell)
{
	t_node	*left;
	t_node	*right;
	t_token_type	op;

	if (minishell->parse_error.type || !minishell->current_token)
		return NULL;

	left = ft_term(minishell);
    if (!left)
		return (NULL);

	while (current_token_is_op(minishell))
	{
		op = minishell->current_token->type;
		get_next_token(minishell);

		if (!minishell->current_token)
			return (set_parse_error(SYNTAX_ERROR), left);
		right = ft_expression(minishell);
		if (!right)
			return (left);
		left = ft_combine(op, left, right, minishell);
		if (!left)
			return (ft_clear_ast(&left, minishell), ft_clear_ast(&right, minishell), NULL);
	}
	return left;
}
