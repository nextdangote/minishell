/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_assemble.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:47:05 by aguede            #+#    #+#             */
/*   Updated: 2024/03/21 16:34:15 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

char	*assemble(char **strings_to_assemble)
{
	char	*assembled_string;
	int		total_n;
	int		i;
	int		offset;

	total_n = 0;
	i = 0;
	while (strings_to_assemble[i] != NULL)
	{
		total_n += ft_strlen(strings_to_assemble[i]);
		i++;
	}
	assembled_string = calloc(total_n + 1, sizeof(char));
	if (assembled_string == NULL)
		return (NULL);
	i = 0;
	offset = 0;
	while (strings_to_assemble[i] != NULL)
	{
		ft_strcat(assembled_string + offset, strings_to_assemble[i]);
		offset += ft_strlen(strings_to_assemble[i]);
		i++;
	}
	return (assembled_string);
}

char	*indeed_expand(char *to_expand, char *b_equal[], char **a_equal)
{
	int	k;

	k = 0;
	while (b_equal[k] != NULL)
	{
		if (ft_strncmp(to_expand + 1, b_equal[k], ft_strlen(b_equal[k])) == 0)
			break ;
		k++;
	}
	return (ft_strdup(a_equal[k]));
}

// char	*remove_single_quote_2(char *str)
// {
// 	int		i;
// 	int		j;
// 	int		n;
// 	char	*updated_str;

// 	n = 0;
// 	i = 0;
// 	j = 0;
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] == '\'')
// 			n++;
// 		i++;
// 	}
// 	updated_str = calloc((ft_strlen(str) - n + 1), sizeof(char));
// 	if (!updated_str)
// 		return (NULL);
// 	while (str[i] != '\0')
// 	{
// 		if (str[i] != '\'')
// 		{
// 			updated_str[j] = str[i];
// 			j++;
// 		}
// 		i++;
// 	}
// 	updated_str[j] = '\0';
// 	return (updated_str);
// }

char	*rem_quote(char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (str[i] != '\'')
		{
			str[j++] = str[i];
		}
		i++;
	}
	str[j] = '\0';
	return (str);
}

char	*expand_assemble(char **str, char **b_equal, char **a_equal)
{
	int		i;
	int		n;
	char	**expanded_str;
	char	*assembled_expanded_str;
	char	*noquotes;

	i = 0;
	n = 0;
	while (str[n] != NULL)
		n++;
	expanded_str = calloc(n + 1, sizeof(char *));
	if (!expanded_str)
		return (NULL);
	i = 0;
	while (i < n)
	{
		if ((check_if_expand(str[i], b_equal)))
			expanded_str[i] = indeed_expand(str[i], b_equal, a_equal);
		else
			expanded_str[i] = ft_strdup(str[i]);
		i++;
	}
	expanded_str[i] = NULL;
	assembled_expanded_str = assemble(expanded_str);
	return (noquotes = rem_quote(assembled_expanded_str), noquotes);
}

// 2 lines out of expand_assemble
// 3 lines out of remove_single_quote 2