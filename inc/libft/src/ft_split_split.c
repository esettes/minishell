/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_split.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:15:49 by uherrero          #+#    #+#             */
/*   Updated: 2023/12/14 21:37:47 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

void	free_split_split(char **s)
{
	int	i;

	i = 0;
	while (s[i])
		free(s[i++]);
	free(s);
	s = NULL;
}

static size_t	split_len_new(char **s, char *delimiter)
{
	size_t	len;
	char	*aux;
	char	*start;

	len = 0;
	while (NULL != *s)
	{
		aux = *s;
		start = *s;
		while (NULL != aux && '\0' != *s[0])
		{
			len++;
			aux = ft_strnstr(*s, delimiter, ft_strlen(*s));
			if (*s == aux)
				*s += ft_strlen(delimiter);
			else
				*s += (aux - *s);
		}
		*s = start;
		s++;
	}
	return (len);
}

static int	need_split(char **s, char *delimiter)
{
	while (NULL != *s)
	{
		if (NULL != ft_strnstr(*s, delimiter, ft_strlen(*s)))
			return (EXIT_SUCCESS);
		s++;
	}
	return (EXIT_FAILURE);
}

static char	**split_core(char **s, char *delimiter)
{
	char	**splited;
	char	**start;
	char	*aux;
	char	*comienzo;
	size_t		debug;

	debug = split_len_new(s, delimiter);
	splited = (char **) ft_calloc(debug + 1, sizeof(char *));
	if (NULL == splited)
		exit(-66);
	start = splited;
	while (NULL != *s)/*bucle de palabras*/
	{
		comienzo = *s;
		while (TRUE)/*maquina de estados*/
		{
			aux = ft_strnstr(*s, delimiter, ft_strlen(*s));
			if (NULL == aux)
				break;
			if (*s == aux)
			{
				*splited = ft_substr(*s, ZERO, ft_strlen(delimiter));
				*s += ft_strlen(delimiter);
			}
			else
			{
				*splited = ft_substr(*s, ZERO, aux - *s);
				*s += (aux - *s);
			}
			splited++;
		}
		if ('\0' != *s[0])
		{
			*splited = ft_strdup(*s);
			splited++;
		}
		*s = comienzo;
		s++;
	}
	return (start);
}

char	**ft_split_split(char **s, char *delimiter)
{
	char	**splited;

	if (NULL == s || NULL == delimiter || NULL == *s)
		return (NULL);
	if (!need_split(s, delimiter))
	{
		splited = split_core(s, delimiter);
		free_split_split(s);
	}
	else
	{
		splited = s;
	}
	return (splited);
}
