/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aguede <aguede@student.42berlin.de>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/20 20:36:23 by aguede            #+#    #+#             */
/*   Updated: 2024/03/20 20:36:48 by aguede           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "expander.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	s = (char *)s;
	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

int	ft_strncmp(char *s1, char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (n && s1[i] && s2[i] && (s1[i] == s2[i]))
	{
		++i;
		--n;
	}
	if (n == 0)
		return (0);
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

size_t	ft_strncpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	src_len = 0;
	i = 0;
	while (src[src_len] != '\0')
	{
		src_len++;
	}
	while (i < size && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	while (i < size)
	{
		dst[i] = '\0';
		i++;
	}
	return (src_len);
}

char	*ft_strdup(const char *s1)
{
	char	*nouveau;
	int		i;
	int		longueur;

	i = 0;
	longueur = ft_strlen(s1);
	nouveau = calloc((longueur + 1), sizeof(char));
	if (!nouveau)
	{
		return (NULL);
	}
	while (s1[i] != '\0')
	{
		nouveau[i] = s1[i];
		i++;
	}
	nouveau[i] = '\0';
	return (nouveau);
}

char	*ft_strchr(const char *s, int c)
{
	size_t	len;
	size_t	j;

	j = 0;
	len = ft_strlen(s);
	if (s[j] == (char)c)
	{
		return ((char *)&s[j]);
	}
	while (s[j] != (char)c && j < len)
	{
		j++;
		if (s[j] == (char)c)
		{
			return ((char *)&s[j]);
		}
	}
	return (NULL);
}
