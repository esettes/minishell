/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uliherre <uliherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:15:49 by uherrero          #+#    #+#             */
/*   Updated: 2023/06/06 18:19:05 by uliherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

static void	free_split_s(char **str, int i)
{
	while (i-- >= ZERO)
	{
		free(str[i]);
		str[i] = NULL;
	}
	free(str);
	str = NULL;
}

static size_t	count_word(char const *s)
{
	register size_t	size;

	size = ZERO;
	while ('\0' != *s)
	{
		while (ft_isspace(*s) && '\0' != *s)
			s++;
		while (!ft_isspace(*s) && '\0' != *s)
			s++;
		if (!ft_isspace(*(s - 1)))
			size++;
	}
	return (size);
}

char	**ft_special_split(char const *s)
{
	register char		**str;
	register char const	*start;
	register size_t		i;
	register size_t		size;

	if (NULL == s)
		return (NULL);
	size = count_word(s);
	str = (char **) ft_calloc(1 + size, sizeof(char *));
	if (NULL == str)
		return (NULL);
	i = ZERO;
	while (ZERO != size--)
	{
		while (ft_isspace(*s))
			s++;
		start = s;
		while ('\0' != *s && !ft_isspace(*s))
			s++;
		str[i++] = ft_substr(start, ZERO, s - start);
		if (NULL == str[i - 1])
			free_split_s(str, i);
	}
	return (str);
}
