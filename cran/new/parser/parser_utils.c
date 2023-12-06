#include "lumumbash.h"


void	ft_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)s)[i] = 0;
		i++;
	}
}


char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return NULL;
	total_length = strlen(s1) + strlen(s2) + 1;
	joined = calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (joined);
}


bool current_token_is_op(t_minishell *minishell) 
{
    t_token_type	type;

	if (!minishell->current_token)
		return (false);
	type = minishell->current_token->type;
	if (type == TOKEN_PIPE)
		return (true);
	return (false);
}



void get_next_token(t_minishell *minishell) {


    minishell->current_token = minishell->current_token->next;

}

void	ft_clear_redir_list(t_redir_node **list)
{
	t_redir_node	*current_node;
	t_redir_node	*next;

	current_node = *list;
	if (!current_node)
		return ;
	while (current_node)
	{
		free(current_node->value);
		next = current_node->next;
		free(current_node);
		current_node = next;
	}
	*list = NULL;
}

void	ft_clear_cmd_node(t_node *node)
{
	if (!node)
		return;
	ft_clear_redir_list(&(node->redir_list));
	free(node->args);
}

void	ft_recursive_clear_ast(t_node *node)
{
	if (!node)
		return ;
	if (node -> type == NODE_CMD)
		ft_clear_cmd_node(node);
	else
	{
		if (node->left)
			ft_recursive_clear_ast(node->left);
		if (node->right)
			ft_recursive_clear_ast(node->right);
	}
	free(node);
}

void	ft_clear_ast(t_node **ast, t_minishell *minishell)
{
	t_token **tokens = &(minishell->tokens); // needed?

	ft_recursive_clear_ast(*ast);
	*ast = NULL;
	if (tokens)
		clear_token_list(&(minishell->tokens));
}


bool	is_redir(t_token_type type)
{
	if (type == TOKEN_INPUT_REDIRECTION || type == TOKEN_OUTPUT_REDIRECTION
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT_REDIRECTION)
		return (true);
	return (false);
}



char	*ft_strjoin_with(char const *s1, char const *s2, char c)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
	if (!c || !strlen(s1) || !strlen(s2))
		return (ft_strjoin(s1, s2));
	total_length = strlen(s1) + strlen(s2) + 1 + 1;
	joined = calloc(total_length, sizeof(char));
	if (!joined)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		joined[i] = s1[i];
		i++;
	}
	joined[i++] = c;
	j = 0;
	while (s2[j])
		joined[i++] = s2[j++];
	joined[i] = 0;
	return (joined);
}


bool ft_join_args(char **args, t_minishell *minishell) 
{
    char *to_free;

    if (minishell->parse_error.type)
        return false;
    if (!*args)
		*args = strdup("");
	if (!*args)
		return (false);

    while (minishell->current_token && minishell->current_token->type == TOKEN_WORD) 
    {
        to_free = *args;
		*args = ft_strjoin_with(*args, minishell->current_token-> value, ' ');
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		get_next_token(minishell);
	}
	return (true);
}



bool get_redir_list(t_redir_node **redir_list, t_minishell *minishell) 
{
    t_token_type redir_type;
    t_redir_node *tmp_redir_node;

    
    if (minishell->parse_error.type) {
        return false;
    }

    while (minishell->current_token && is_redir(minishell->current_token->type)) 
    {
        redir_type = minishell->current_token->type;
        get_next_token(minishell);

        if (!minishell->current_token) {
            return set_parse_error(SYNTAX_ERROR), false;
        }

        if (minishell->current_token->type != TOKEN_WORD) {
            return set_parse_error(SYNTAX_ERROR), false;
        }

        tmp_redir_node = new_redir_node(redir_type, minishell->current_token->value);

        if (!tmp_redir_node) {
            return set_parse_error(MALLOC_ERROR), false;
        }

        append_redir_node(redir_list, tmp_redir_node);
        get_next_token(minishell);
    }

    return true;
}
