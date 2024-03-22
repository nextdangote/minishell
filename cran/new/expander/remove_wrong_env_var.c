/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_wrong_env_var.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 21:51:52 by aguede            #+#    #+#             */
/*   Updated: 2024/03/20 21:54:16 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	**fill_the_double_d(int n, char **before_equal, char **str)
{
	int		i;
	int		k;
	char	**removed_wrong_env_var;

	removed_wrong_env_var = calloc(n, sizeof(char *));
	if (!removed_wrong_env_var)
		return (NULL);
	i = 0;
	k = 0;
	while (str[i] != NULL)
	{
		if (!(str[i][0] == '$' && !check_if_expand(str[i], before_equal)))
		{
			removed_wrong_env_var[k] = ft_strdup(str[i]);
			k++;
		}
		i++;
	}
	removed_wrong_env_var[k] = NULL;
	return (removed_wrong_env_var);
}

char	**remove_wrong_env_var(char **str, char **before_equal)
{
	int		i;
	int		j;
	int		k;
	int		tmp;
	char	**removed_wrong_env_var;

	i = 0;
	j = 0;
	k = 0;
	while (str[i] != NULL)
	{
		if ((str[i][0] == '$' && !check_if_expand(str[i], before_equal)))
			j++;
		i++;
	}
	tmp = i - j + 1;
	removed_wrong_env_var = fill_the_double_d(tmp, before_equal, str);
	return (removed_wrong_env_var);
}
