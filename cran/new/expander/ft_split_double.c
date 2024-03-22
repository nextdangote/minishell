/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_double.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 16:54:32 by aguede            #+#    #+#             */
/*   Updated: 2024/03/21 18:23:00 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"
// ! faire iune condition de si il n'y a pas de dollar dedans le count word est 1
// atm final strings empty with 10 spaces
char	**all_in_one(char **final_strings, char ***triple_d_str)
{
	int	i;
	int	j;
	int	k;

	i = 0;
	j = 0;
	k = 0;
	while (triple_d_str[i] != NULL)
	{
		j = 0;
		while (triple_d_str[i][j] != NULL)
		{
			printf("inside all in one k = %d, i = %d, j = %d\n", k, i, j);
			final_strings[k] = triple_d_str[i][j];
			k++;
			j++;
		}
		i++;
		printf("big while loop inside all in one k = %d, i = %d, j = %d\n", k, i, j);
	}
	final_strings[k] = NULL;
	return (final_strings);
}

char	**ft_string_to_double_d(char *str)
{
	char	**str_double;

	str_double = calloc(2, sizeof(char *));
	if (!str_double)
		return (NULL);
	str_double[0] = ft_strdup(str);
	str_double[1] = NULL;
	return (str_double);
}

// char	**ft_split_double(char **str, char c)
// {
// 	int		i;
// 	int		j;
// 	int		total;
// 	char	***new_str_str;
// 	char	**final_strings;

// 	i = 0;
// 	j = 0;
// 	while (str[i] != NULL)
// 		i++;
// 	new_str_str = calloc(i + 1, sizeof(char **));
// 	if (!new_str_str)
// 		return (NULL);
// 	i = 0;
// 	while (str[i] != NULL)
// 	{
// 		if (str[i][0] != '\'')
// 			new_str_str[j] = ft_split_bis(str[i], c);
// 		else
// 			new_str_str[j] = ft_string_to_double_d(str[i]);
// 		i++;
// 		j++;
// 	}
// 	new_str_str[j] = NULL;
// 	total = count_number_of_words(new_str_str);
// 	final_strings = calloc(total + 1, sizeof(char *));
// 	if (!final_strings)
// 		return (NULL);
// 	final_strings = all_in_one(final_strings, new_str_str);
// 	return (final_strings);
// }

char	***allocate_and_populate_new_str_str(char **str, char c,
		int *total_words)
{
	int		i;
	int		j;
	char	***new_str_str;

	i = 0;
	j = 0;
	while (str[i] != NULL)
		i++;
	ft_print_double_d(str, "allocate and populate in ft_split_double", -1);
	printf("number of double d arrays of new_str_str inside alloc and populate : %d\n", i);
	new_str_str = calloc(i + 1, sizeof(char **));
	if (!new_str_str)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		if (str[i][0] != '\'')
			new_str_str[j] = ft_split_bis(str[i], c);
		else
			new_str_str[j] = ft_string_to_double_d(str[i]);
		i++;
		j++;
	}
	new_str_str[j] = NULL;
	*total_words = j;
	return (new_str_str);
}

char	**create_final_strings(char ***new_str_str, int total)
{
	int		total_words;
	char	**final_strings;

	(void)total;
	total_words = count_number_of_words(new_str_str);
	printf("total amount of words is : %d\n", total_words);
	final_strings = calloc(total_words + 1, sizeof(char *));
	if (!final_strings)
		return (NULL);
	final_strings = all_in_one(final_strings, new_str_str);
	return (final_strings);
}

void free_new_str_str(char ***new_str_str) 
{
    if (new_str_str) {
        int i = 0;
        while (new_str_str[i] != NULL) 
		{
            if (new_str_str[i]) 
			{
                char **current_array = new_str_str[i];
                if (current_array) 
				{
                    int j = 0;
                    while (current_array[j] != NULL) 
					{
                        free(current_array[j]); // Free each string
                        current_array[j] = NULL; // Set pointer to NULL after freeing
                        j++;
                    }
                    free(current_array); // Free the double pointer array
                    new_str_str[i] = NULL; // Set pointer to NULL after freeing
                }
            }
            i++;
        }
        free(new_str_str); // Free the main array of pointers
    }
}

char	**ft_split_double(char **str, char c)
{
	int		total_words;
	char	***new_str_str;
	char	**final_strings;

	new_str_str = allocate_and_populate_new_str_str(str, c, &total_words);
	if (!new_str_str)
		return (NULL);
	final_strings = create_final_strings(new_str_str, total_words);
	//free(new_str_str);
	//free_new_str_str(new_str_str);
	return (final_strings);
}
