/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:18:41 by aguede            #+#    #+#             */
/*   Updated: 2024/03/21 17:37:53 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

int	check_if_expand(char *str, char **p1)
{
	int	i;

	i = 0;
	if (str[0] == '$')
	{
		while (p1[i] != NULL)
		{
			if (ft_strncmp(str + 1, p1[i],
					ft_strlen(p1[i])) == 0
				&& (ft_strlen(p1[i]) == (ft_strlen(str) - 1)))
			{
				return (1);
			}
			i++;
		}
	}
	return (0);
}

int	check_dollar_word_expand(char **dollar_separated_str, char **p1)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (dollar_separated_str[i] != NULL)
	{
		if (dollar_separated_str[i][0] == '$')
		{
			if (check_if_expand(dollar_separated_str[i], p1))
				j++;
		}
		i++;
	}
	return (j);
}

int	check_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i] != 0)
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

t_token	*expander(t_token *tokens, char **env)
{
	t_lists_env	envi;
	char		**div_by_quote = NULL;
	t_token		*head;
	char		**div_by_doll = NULL;
	char		**clean = NULL;

	envi = split_lists_env(env);
	head = tokens;
	while (tokens != NULL)
	{
		if (tokens->type == TOKEN_WORD
			&& check_dollar(tokens->value))
		{
			div_by_quote = new_ft_split(tokens->value, '\'');
			ft_print_double_d(div_by_quote, "expander after div_by_quote", -1);
			div_by_doll = ft_split_double(div_by_quote, '$');
			ft_print_double_d(div_by_doll, "expander after div_by_doll", -1);
			if ((check_dollar_word_expand(div_by_doll, envi.p1)) >= 1)
			{
				clean = remove_wrong_env_var(div_by_doll, envi.p1);
				tokens->value = expand_assemble(clean, envi.p1, envi.p2);
			}
		}
		tokens = tokens->next;
	}
	free_double_d(envi.p1);
	free_double_d(envi.p2);
	free_double_d(div_by_quote);
	free_double_d(clean);
	//free_everything(envi, div_by_doll, div_by_quote, clean);
	return (head);
}

// echo hello users 'hi' how are you '$USER' doing $SHELL $USERT oh $hey jjk

// reduce the size of iop[]=more than 25 lines functions : 12 lines left
// issues : leaks and invalid size read -> 
//free_everything(envi, div_by_doll, div_by_quote, clean);
// have to fix the case of $?
// handle adding a env var and the tilde.
// rest of minishell : signals, proper execve, cd, export, unset, env