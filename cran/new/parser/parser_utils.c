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


// bool current_token_is_op(t_token *current_token) {
bool current_token_is_op(t_minishell *minishell) 
{
    t_token *current_token;
	current_token = minishell->current_token; // added?
	
	if (!current_token) {
        return false;
    }
    t_token_type type = current_token->type;
    return (type == TOKEN_PIPE);
}

void get_next_token(t_minishell *minishell) {
    if (minishell && minishell->current_token) {
        minishell->current_token = minishell->current_token->next;
    }
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


// char	*ft_strjoin_with(char const *s1, char const *s2, char c)
// {
// 	char	*joined;
// 	size_t	total_length;
// 	size_t	i;
// 	size_t	j;

// 	if (!s1 || !s2)
// 		return NULL;
// 	if (!c || !strlen(s1) || !strlen(s2))
// 		return (ft_strjoin(s1, s2));
// 	total_length = strlen(s1) + strlen(s2) + 1 + 1;
// 	joined = calloc(total_length, sizeof(char));
// 	if (!joined)
// 		return NULL;
// 	i = 0;
// 	while (s1[i])
// 	{
// 		joined[i] = s1[i];
// 		i++;
// 	}

// 	if (s1[0] != '\0' && s2[0] != '\0')
//     {
//         joined[i++] = c;
//     }



// 	// joined[i++] = c; go back to this?


// 	j = 0;
// 	while (s2[j])
// 		joined[i++] = s2[j++];
// 	joined[i] = 0;
// 	return (joined);
// }


char *ft_strjoin_with(char const *s1, char const *s2, char const *separator)
{
    char *joined;
    size_t total_length;
    size_t i;
    size_t j;

    if (!s1 || !s2)
        return NULL;

    size_t separator_length = strlen(separator);
    total_length = strlen(s1) + separator_length + strlen(s2) + 1;
    joined = calloc(total_length, sizeof(char));

    if (!joined)
        return NULL;

    i = 0;
    while (s1[i])
    {
        joined[i] = s1[i];
        i++;
    }

    if (s1[0] != '\0' && s2[0] != '\0')
    {
        for (size_t k = 0; k < separator_length; k++)
        {
            joined[i++] = separator[k];
        }
    }

    j = 0;
    while (s2[j])
        joined[i++] = s2[j++];

    joined[i] = 0;
    return joined;
}


// bool ft_join_args(char ***args, t_minishell *minishell) 
// {
//     if (minishell->parse_error.type) {
//         return false;
//     }

//     char *to_free;

//     // if (!*args) {
//     //     *args = strdup("");
//     // }

//     // if (!*args) {
//     //     return false;
//     // }

// 	if (!*args) {
//         *args = (char **)malloc(sizeof(char *));
//         if (!*args) {
//             return false;
//         }
//         **args = NULL;
//     }

//     while (minishell->current_token && minishell->current_token->type == TOKEN_WORD) 
//     {
//         to_free = **args;
//         **args = ft_strjoin_with(**args, minishell->current_token->value, ' ');

//         if (!**args) {
//             free(to_free);
//             return false;
//         }

//         free(to_free);
//         get_next_token(minishell);
//     }

//     return true;
// }

// bool ft_join_args(char ***args, t_minishell *minishell) 
// {
//     if (minishell->parse_error.type) {
//         return false;
//     }

//     char *to_free;

//     if (!*args) {
//         *args = (char **)malloc(sizeof(char *));
//         if (!*args) {
//             return false;
//         }
//         **args = NULL;
//     }

//     while (minishell->current_token && minishell->current_token->type == TOKEN_WORD) 
//     {
//         if (minishell->current_token->value != NULL) {
//             char *temp = ft_strjoin_with(**args, minishell->current_token->value, ' ');
//             if (!temp) {
//                 return false;
//             }

//             free(**args);
//             **args = temp;
//         }

//         get_next_token(minishell);

//         if (!minishell->current_token) {
//             break;
//         }
//     }

//     return true;
// }
bool ft_join_args(char ***args, t_minishell *minishell) 
{
    if (minishell->parse_error.type) {
        return false;
    }

    char *to_free;

    if (!*args) {
        *args = (char **)malloc(sizeof(char *));
        if (!*args) {
            return false;
        }
        **args = NULL;
    }

    while (minishell->current_token && minishell->current_token->type == TOKEN_WORD) 
    {
        // Ensure the value is not NULL before attempting to concatenate
        if (minishell->current_token->value != NULL) {
            // Use a temporary variable for concatenation
            char *separator = (**args && **args[0] != '\0') ? " " : "";  // Only add separator if not at the beginning
            char *temp = ft_strjoin_with(**args, minishell->current_token->value ,separator);
            if (!temp) {
                // Handle memory allocation error
                return false;
            }

            // Free the previous value and update to the new concatenated value
            free(**args);
            **args = temp;
        }

        get_next_token(minishell);

        // Check if the next token is NULL and break out of the loop
        if (!minishell->current_token) {
            break;
        }
    }

    return true;
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
            return set_parse_error(SYNTAX_ERROR, minishell), false;
        }

        if (minishell->current_token->type != TOKEN_WORD) {
            return set_parse_error(SYNTAX_ERROR, minishell), false;
        }

        tmp_redir_node = new_redir_node(redir_type, minishell->current_token->value);

        if (!tmp_redir_node) {
            return set_parse_error(MALLOC_ERROR, minishell), false;
        }

        append_redir_node(redir_list, tmp_redir_node);
        get_next_token(minishell);
    }

    return true;
}
