/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tester_functions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:53:25 by aguede            #+#    #+#             */
/*   Updated: 2024/03/21 17:42:19 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

void	ft_print_double_d(char **str, char *from, int n)
{
	int	i;

	i = 0;
	if (n == -1)
	{
		while (str[i] != NULL)
		{
			printf("from %s : %s\n", from, str[i]);
			i++;
		}
		printf("from %s : %s\n", from, str[i]);
	}
	else
	{
		while (str[i] != NULL)
		{
			printf("nbr %d from %s : %s\n", n, from, str[i]);
			i++;
		}
	}
}

int	count_number_of_words(char ***triple_d_str)
{
	int			i;
	int			j;
	static int	total;

	i = 0;
	total = 0;
	while (triple_d_str[i] != NULL)
	{
		j = 0;
		while (triple_d_str[i][j] != NULL)
		{
			total++;
			j++;
		}
		i++;
	}
	return (total);
}

char	*ft_strcat(char *dest, char *src)
{
	int	i;
	int	j;

	i = 0;
	while (dest[i] != '\0')
		i++;
	j = 0;
	while (src[j] != '\0')
	{
		dest[i + j] = src[j];
		j++;
	}
	dest[i + j] = '\0';
	return (dest);
}

void	free_everything(t_lists_env envi,char **div_by_doll,char **div_by_quote,char **clean)
{
	free_double_d(div_by_doll);
	//(void)div_by_doll;
	free_double_d(div_by_quote);
	//(void)clean;
	free_double_d(clean);
	free_double_d(envi.p1);
	free_double_d(envi.p2);
	free_double_d(div_by_doll);
}