#include "lumumbash.h"


t_node	*ft_parse(t_minishell *minishell)
{
	t_node	*ast;

	minishell->current_token = minishell->tokens;
	ast = ft_expression(minishell);
	if (minishell->current_token)
    {
		set_parse_error(SYNTAX_ERROR, minishell); 
        return ast;
    }
	return (ast);
}
