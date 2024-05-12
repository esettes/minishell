/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:47:13 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 11:21:13 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

static	size_t	cnt_words(char const *s, char c)
{
	size_t	count;
	size_t	i;

	i = 0;
	count = 0;
	while (s[i] != '\0')
	{
		while (s[i] == c)
			i++;
		if (s[i])
			count++;
		while (s[i] && s[i] != c)
			i++;
	}
	return (count);
}

static	char	**ft_free_memory(char **array, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(array[i]);
		i++;
	}
	free(array);
	return (NULL);
}

static	char	**ft_string(char const *s, char **array, char c)
{
	size_t	len;
	size_t	i;

	i = 0;
	while (*s)
	{
		len = 0;
		while (*s == c)
			s++;
		if (*s)
		{
			while (*s != c && *s)
			{
				s++;
				len++;
			}
			array[i] = ft_substr((s - len), 0, len);
			if (array[i] == 0)
				return (ft_free_memory(array, i));
			i++;
		}
	}
	array[i] = NULL;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	char	**array;

	array = (char **)malloc((cnt_words(s, c) + 1) * sizeof(char *));
	if (array == 0)
		return (0);
	return (ft_string(s, array, c));
}
