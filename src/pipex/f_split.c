/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_split.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:55:18 by iostancu          #+#    #+#             */
/*   Updated: 2024/01/31 19:24:19 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

char	**free_memory(const char **arr, size_t pos)
{
	while (pos--)
		free ((void *)arr[pos]);
	free(arr);
	return (NULL);
}

static size_t	str_count(char const *s, char c)
{
	size_t	count;
	size_t	bo;
	char	*a;

	count = 0;
	bo = 0;
	a = (char *)s;
	while (*a)
	{
		if (*a != c && bo == 0)
		{
			count++;
			bo = 1;
		}
		if (*a == c)
			bo = 0;
		a++;
	}
	return (count);
}

static void	*set_pos(char const *s, size_t j_init, size_t i_fin)
{
	size_t	j;
	char	*str;
	char	*b;

	j = 0;
	str = malloc(sizeof(char) * (i_fin - j_init + 1));
	b = (char *)s;
	if (!str)
		return (NULL);
	while (j_init < i_fin)
		str[j++] = b[j_init++];
	str[j] = '\0';
	return (str);
}

char	**f_split(char const *s, char c)
{
	char	**arr;
	size_t	i;
	size_t	j;
	size_t	pos;

	i = -1;
	pos = 0;
	arr = malloc(sizeof(char *) * ((str_count(s, c)) + 1));
	if (!arr)
		return (NULL);
	while (++i < f_strlen(s) && pos < str_count(s, c))
	{
		if (*(s + i) != c)
		{
			j = i;
			while (i <= f_strlen(s) && *(s + i) != c && *s)
				i++;
			arr[pos++] = set_pos(s, j, i);
			if (arr[pos - 1] == NULL)
				return (free_memory((const char **)arr, pos));
		}
	}
	arr[pos] = 0;
	return (arr);
}
