#include "tokenizer.h"
#include "minishell.h"
#include "parser.h"
#include "header.h"


// parser helpers

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*joined;
	size_t	total_length;
	size_t	i;
	size_t	j;

	if (!s1 || !s2)
		return (NULL);
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
void	ft_free_ch(char **tofree)
{
	size_t	i;

	if (!tofree)
		return ;
	i = 0;
	while (tofree[i])
		free(tofree[i++]);
	free(tofree);
}
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

void	clear_redir_list(t_redir_node **list)
{
	t_redir_node	*curr_node;
	t_redir_node	*next;

	curr_node = *list;
	if (!curr_node)
		return ;
	while (curr_node)
	{
		free(curr_node->value);
		ft_free_ch(curr_node -> expanded_value);
		next = curr_node->next;
		free(curr_node);
		curr_node = next;
	}
	*list = NULL;
}

void	clear_cmd_node(t_node *node)
{
	if (!node)
		return ;
	clear_redir_list(&(node -> redir_list));
	free(node -> args);
	// ft_free_ch(node -> expanded_args);
}

void	recursive_clear_ast(t_node *node)
{
	if (!node)
		return ;
	if (node -> type == NODE_CMD)
		clear_cmd_node(node);
	else
	{
		if (node->left)
			recursive_clear_ast(node->left);
		if (node->right)
			recursive_clear_ast(node->right);
	}
	free(node);
}
// this is in the tokenizer.c file
// void	clear_token_list(t_token **list)
// {
// 	t_token	*curr_node;
// 	t_token	*next;

// 	curr_node = *list;
// 	if (!curr_node)
// 		return ;
// 	while (curr_node)
// 	{
// 		free(curr_node->value);
// 		next = curr_node->next;
// 		free(curr_node);
// 		curr_node = next;
// 	}
// 	*list = NULL;
// }

void	clear_ast(t_node **ast, t_token **tokens)
{
	recursive_clear_ast(*ast);
	*ast = NULL;
	clear_token_list(tokens);
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

t_node_type	get_node_type(t_token_type type)
{
	if (type == TOKEN_PIPE)
		return (NODE_PIPE);
    return NODE_CMD;
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



void	get_next_token(t_minishell *minishell)
{
	minishell->current_token = minishell->current_token -> next;
}

bool	current_token_is_redir(t_minishell *minishell)
{
	t_token_type	type;

	if (!minishell->current_token)
		return (false);
	type = minishell->current_token->type;
	if (type == TOKEN_PIPE)
		return (true);
	return (false);
}

bool	is_redir(t_token_type type)
{
	if (type == TOKEN_INPUT_REDIRECTION || type == TOKEN_OUTPUT_REDIRECTION
		|| type == TOKEN_HEREDOC || type == TOKEN_APPEND_OUTPUT_REDIRECTION)
		return (true);
	return (false);
}

void	set_parse_error(t_parse_error_type type, t_minishell *minishell)
{
	minishell->parse_error.type = type;
}

// t_redir_type	get_redir_type(t_token_type type)
// {
// 	if (type == TOKEN_INPUT_REDIRECTION)
// 		return (REDIR_IN);
// 	if (type == TOKEN_OUTPUT_REDIRECTION)
// 		return (REDIR_OUT);
// 	if (type == TOKEN_HEREDOC)
// 		return (REDIR_HEREDOC);
// 	return (REDIR_APPEND);
// }

// creates a new redir node
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

// creates a new node for ast
t_node	*new_node(t_node_type type)
{
	t_node	*new_node;

	new_node = (t_node *)calloc(1, sizeof(t_node));
	if (!new_node)
		return (NULL);
	new_node->type = type;
	return (new_node);
}

bool	get_redir_list(t_redir_node **redir_list, t_minishell *minishell)
{
	t_token_type		redir_type;
	t_redir_node			*tmp_redir_node;

	if (minishell->parse_error.type)
		return (false);
	while (minishell->current_token && is_redir(minishell->current_token->type))
	{
		redir_type = minishell->current_token->type;
		get_next_token(minishell);
		if (!minishell->current_token)
			return (set_parse_error(SYNTAX_ERROR, minishell), false);
		if (minishell->current_token->type != TOKEN_WORD)
			return (set_parse_error(SYNTAX_ERROR, minishell), false);
		tmp_redir_node = new_redir_node(redir_type, minishell->current_token->value);
		if (!tmp_redir_node)
			return (set_parse_error(MALLOC_ERROR, minishell), false);
		append_redir_node(redir_list, tmp_redir_node);
		get_next_token(minishell);
	}
	return (true);
}

// builds a string containing the concatenated values of consecutive TOKEN_WORD tokens, separated by spaces. useful for constructing command arguments from a sequence of TOKEN_WORD tokens
bool	ft_join_args(char **args, t_minishell *minishell)
{
	char	*to_free;

	if (minishell->parse_error.type)
		return (false);
	if (!*args)
		*args = strdup("");
	if (!*args)
		return (false);
	while (minishell->current_token
		&& minishell->current_token -> type == TOKEN_WORD)
	{
		to_free = *args;
		*args = ft_strjoin_with(*args, minishell->current_token -> value, ' ');
		if (!*args)
			return (free(to_free), false);
		free(to_free);
		get_next_token(minishell);
	}
	return (true);
}

t_node	*get_simple_cmd(t_minishell *minishell)
{
	t_node	*node;

	if (minishell->parse_error.type)
		return (NULL);
	node = new_node(NODE_CMD);
	if (!node)
		return (set_parse_error(MALLOC_ERROR, minishell), NULL);
	while (minishell->current_token
		&& (minishell->current_token->type == TOKEN_WORD
			|| is_redir(minishell->current_token->type)))
	{
		if (minishell->current_token->type == TOKEN_WORD)
		{
			if (!ft_join_args(&(node -> args), minishell))
				return (clear_cmd_node(node), set_parse_error(MALLOC_ERROR, minishell), NULL);
		}
		else if (is_redir(minishell->current_token->type))
		{
			if (!get_redir_list(&(node->redir_list), minishell))
				return (free(node->args), free(node), NULL);
		}
	}
	return (node);
}


// int	ft_prec(t_token_type type)
// {
// 	if (type == T_OR || type == T_AND)
// 		return (0);
// 	return (1);
// }

// int	ft_curr_token_prec(t_minishell *minishell)
// {
// 	return (ft_prec(minishell->current_token->type));
// }

// checks there's no unwanted redir token
t_node	*ft_term(t_minishell *minishell)
{
	// t_node	*node;

	if (minishell->parse_error.type)
		return (NULL);
	if (current_token_is_redir(minishell))
		return (set_parse_error(SYNTAX_ERROR, minishell), NULL);
	else
		return (get_simple_cmd(minishell));
}

// t_node	*ft_combine(t_token_type op, t_node *left, t_node *right)
// {
// 	t_node	*node;
//     t_minishell *minishell;

// if (minishell->parse_error.type)
// 		return (NULL);
// 	node = new_node(get_node_type(op));
// 	if (!node)
// 		return (set_parse_error(MALLOC_ERROR, minishell), NULL);
// 	node -> left = left;
// 	node -> right = right;
// 	return (node);
// }



t_node *ft_combine(t_token_type op, t_node *left, t_node *right, t_minishell *minishell)
{
    t_node *node;

    if (minishell->parse_error.type)
        return (NULL);
    
    node = new_node(get_node_type(op));

    if (!node)
        return (set_parse_error(MALLOC_ERROR, minishell), NULL);

    node->left = left;
    node->right = right;

    return (node);
}

// 
t_node *ft_expression(t_minishell *minishell)
{
    t_node *left;
    t_node *right;
    t_token_type op;

    if (minishell->parse_error.type || !minishell->current_token)
        return (NULL);
    
    left = ft_term(minishell);
    
    if (!left)
        return (NULL);
    
    while (current_token_is_redir(minishell))
    {
        op = minishell->current_token->type;
        get_next_token(minishell);

        if (!minishell->current_token)
            return (set_parse_error(SYNTAX_ERROR, minishell), clear_ast(&left, NULL), NULL);

        right = ft_term(minishell);

        if (!right)
            return (clear_ast(&left, NULL), NULL);

        left = ft_combine(op, left, right, minishell);

        if (!left)
            return (clear_ast(&right, NULL), NULL);
    }

    return (left);
}


void	handle_parse_error(t_minishell *minishell)
{
	t_parse_error_type	type;
	t_token_type		token_type;
	char				**types;

	types = (char *[]){"T_WORD", "<", ">", "<<", ">>", "|", "newline"};
	type = minishell->parse_error.type;
	(void)token_type;
	(void)types;
	if (type)
	{
		if (type == SYNTAX_ERROR)
		{
			if (!minishell->current_token)
				token_type = TOKEN_NL;
			else
				token_type = minishell->current_token->type;
			ft_putstr_fd("lubumbash: syntax error near unexpected token `", 2);
			ft_putstr_fd(types[token_type], 2);
			ft_putstr_fd("'\n", 2);
			minishell->exit_s = 258;
		}
		clear_ast((&minishell->ast), NULL);
		ft_bzero(&minishell->parse_error, sizeof(t_parse_error));
	}
}



// main parsing function
// t_node	*ft_parse(t_minishell *minishell)
// {
//     t_node	*ast;

//     minishell->current_token = minishell->tokens;
//     ast = ft_expression(minishell);
//     if (minishell->current_token)
//         return (set_parse_error(minishell, SYNTAX_ERROR), ast);
//     return (ast);
// }

t_node	*ft_parse(t_minishell *minishell)
{
    t_node	*ast;

    minishell->current_token = minishell->tokens;
    ast = ft_expression(minishell);
    if (minishell->parse_error.type)
        return (ast); // Error already set, just return the AST as is
    if (minishell->current_token)
    {
        set_parse_error(SYNTAX_ERROR, minishell);
        return (ast);
    }
    return (ast);
}
