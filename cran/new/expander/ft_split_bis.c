/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bis.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:51:19 by aguede            #+#    #+#             */
/*   Updated: 2024/03/22 10:17:51 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

// int	ft_countword(const char *s, char c)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (s[i] != 0)
// 	{
// 		if (s[i] == c)
// 		{
// 			count++;
// 			i++;
// 			while (s[i] != 0)
// 			{
// 				if (isspace(s[i]))
// 				{
// 					count++;
// 					break ;
// 				}
// 				i++;
// 			}
// 		}
// 		i++;
// 	}
// 	return (count + 1);
// }

// int	ft_countword(const char *s, char c)
// {
// 	int	count;
// 	int	i;

// 	count = 0;
// 	i = 0;
// 	while (s[i] != 0)
// 	{
// 		if (s[i] == c)
// 		{
// 			count++;
// 			i++;
// 			while (s[i] != 0 || isspace(s[i]))
// 			{
// 				if (isspace(s[i]))
// 					count++;
// 				i++;
// 			}
// 		}
// 		if (s[i] != 0)
// 			i++;
// 	}
// 	if (s[i] == '$')
// 		return (count);
// 	return (count + 1);
// }
int	ft_dollar(char *str)
{
	int i;
	
	i = 0;
	printf("inside ft_dollar\n");
	while(str[i] != '\0')
	{
		if (str[i] == '$')
			return (1);
		i++;
	}
	return (0);
}

int	ft_countword(char *str, char c)
{
	int	i;
	int	n;
	int flag;
	char	*tmp;
	
	i = 1;
	n = 0;
	flag = 0;
	tmp = strdup(str);
	if (!ft_dollar(str))
	{
		printf("inside ft_dollar condition\n");
		return (1);
	}
	
	while(*tmp)
	{
		if (*tmp == c)
			flag = 1;
		if ((*tmp == c && n == 1) || (flag == 1 && isspace(*tmp)))
		{
			i++;
			n = 0;
			if (isspace(*tmp))
				flag = 0;
			//while(*tmp && *tmp != c && 
		}
		n = 1;
		tmp++;
	}
	//if (str[0] == c)
	//	return(i + 1);
	return (i);
}
// char	*fill_the_word(char *str, int end, char *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (i < end)
// 	{
// 		lst[i] = str[i];
// 		i++;
// 	}
// 	lst[i] = 0;
// 	return (lst);
// }
char	*fill_the_word(char *str, int end, char *lst)
{
	int	i;
	int	tmp;

	tmp = end;
	while (end > 0)
	{
		str--;
		end--;
	}
	i = 0;
	while (i < tmp)
	{
		lst[i] = str[i];
		i++;
	}
	(void)str;
	lst[i] = 0;
	return (lst);
}
// char	**fill_lst(char	*str)
// char	**ft_split_bis(char *str, char c)
// {
// 	char	**lst;
// 	int		i;
// 	int		j;
// 	int		reset;
// 	int		flag;

// 	reset = 0;
// 	j = 0;
// 	lst = calloc((ft_countword(str, c) + 1), sizeof(char *));
// 	if (!str || !lst)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != '\0')
// 	{
// 		flag = 0;
// 		while ((reset > 0 && str[i] != c) || reset == 0)
// 		{
// 			if (str[i] == c)
// 				flag = 1;
// 			if ((flag == 1 && isspace(str[i])) || str[i] == 0)
// 				break ;
// 			i++;
// 			reset++;
// 		}
// 		lst[j] = calloc(reset + 1, sizeof(char));
// 		lst[j] = fill_the_word(str, i, (i - reset), lst[j]);
// 		j++;
// 		reset = 0;
// 	}
// 	lst[j] = NULL;
// 	return (lst);
// }

char	**allocate_memory(char *str, char c)
{
	char	**lst;
	//if(dollar_is_)
	lst = calloc((ft_countword(str, c) + 1), sizeof(char *));
	printf("amount of words for \"%s\" inside allocate_memory is : %d\n",str, ft_countword(str, c) + 1 );
	if (!str || !lst)
		return (NULL);
	return (lst);
}

char	**fill_array(char **lst, char *str, char c)
{
	int	j;
	int	reset;
	int	flag;

	j = 0;
	reset = 0;
	while (*str != '\0')
	{
		flag = 0;
		while ((reset > 0 && *str != c) || reset == 0)
		{
			if (*str == c)
				flag = 1;
			if ((flag == 1 && isspace(*str)) || *str == 0)
				break ;
			str++;
			reset++;
		}
		lst[j] = calloc(reset + 1, sizeof(char));
		lst[j] = fill_the_word(str, reset, lst[j]);
		j++;
		reset = 0;
	}
	return (lst[j] = NULL, lst);
}

char	**ft_split_bis(char *str, char c)
{
	char	**lst;
	char	*tmp;

	tmp = ft_strdup(str);
	lst = allocate_memory(str, c);
	if (!lst)
		return (NULL);
	return (fill_array(lst, tmp, c));
}

// 6 lines out of ft_split_bis
// idea of doing calloc inside fill the word
// 1 line in ft countword
