#include "lumumbash.h"


static t_node *get_simple_cmd(t_minishell *minishell) 
{
    if (minishell->parse_error.type) {
        return NULL;
    }
    
    t_node *node = new_node(NODE_CMD);
    
    if (!node) {
        set_parse_error(MALLOC_ERROR, minishell);
        return NULL;
    }

	node->args = NULL;

    while (minishell->current_token && (minishell->current_token->type == TOKEN_WORD || is_redir(minishell->current_token->type))) {
        if (minishell->current_token->type == TOKEN_WORD) {
			printf("Before condition: node=%p, node->args=%p\n", (void *)node, (void *)(node ? node->args : NULL));


			if (!node || !node->args) {
				printf("Malloc error condition triggered\n");
                set_parse_error(MALLOC_ERROR, minishell);
                // ft_clear_ast(&(node->redir_list), minishell);
                free(node);
                return NULL;
            }
            if (!ft_join_args(&(node->args), minishell)) {
                ft_clear_cmd_node(node);
                set_parse_error(MALLOC_ERROR, minishell);
				//REMOVE 2 LINES BELOW?
				// ft_clear_ast(&(node->redir_list), minishell);
                // free(node);

                return NULL;
            }
        } else if (is_redir(minishell->current_token->type)) {
            if (!get_redir_list(&(node->redir_list), minishell)) {
				// ft_clear_ast(&(node->redir_list), minishell); // remove this?
                free(node->args);
                free(node);
                return NULL;
            }
        }
    }

    return node;
}


t_node	*ft_term(t_minishell *minishell)
{
	t_node	*node;

	if (minishell->parse_error.type)
		return NULL;
	if (current_token_is_op(minishell)) {
		set_parse_error(SYNTAX_ERROR, minishell);
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
		return (set_parse_error(MALLOC_ERROR, minishell), NULL);
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
			return (set_parse_error(SYNTAX_ERROR, minishell), left);
            //return ft_set_parse_err(E_SYNTAX, minishell), ft_clear_ast(&left), NULL;

		right = ft_term(minishell);
		// right = ft_expression(minishell);

		if (!right) {
			// return (ft_clear_ast(&left, minishell), NULL);
			// return (ft_clear_ast(&left, NULL), NULL);
			set_parse_error(SYNTAX_ERROR, minishell);
            ft_clear_ast(&left, minishell);
			return (left);

		}
		left = ft_combine(op, left, right, minishell);

		if (!left)
			// return (ft_clear_ast(&right, minishell), NULL);
			return (ft_clear_ast(&left, minishell), ft_clear_ast(&right, minishell), NULL);
			// set_parse_error(SYNTAX_ERROR, minishell);
            // ft_clear_ast(&left, minishell);


	}

	return left;
}
