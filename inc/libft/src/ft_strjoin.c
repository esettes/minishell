/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: uliherre <uliherre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 18:03:01 by uherrero          #+#    #+#             */
/*   Updated: 2024/02/04 00:13:03 by uliherre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	register char	*nw_str;
	register char	*start;

	if (NULL == s1 || NULL == s2)
		return (NULL);
	nw_str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	start = nw_str;
	if (NULL != nw_str)
	{
		while ('\0' != *s1)
			*(nw_str++) = *(s1++);
		while ('\0' != *s2)
			*(nw_str++) = *(s2++);
	}
	return (start);
}
char	*ft_strjoin_f1(char const *s1, char const *s2)
{
	register char	*nw_str;
	register char	*start;
	char			*s1_start;

	if (NULL == s1 || NULL == s2)
		return (free((void *)s1), NULL);
	nw_str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	start = nw_str;
	s1_start = (char *)s1;
	if (NULL != nw_str)
	{
		while ('\0' != *s1)
			*(nw_str++) = *(s1++);
		while ('\0' != *s2)
			*(nw_str++) = *(s2++);
	}
	free(s1_start);
	return (start);
}

char	*ft_strjoin_f2(char const *s1, char const *s2)
{
	register char	*nw_str;
	register char	*start;
	char	*s2_start;

	if (NULL == s1 || NULL == s2)
		return (free((void *)s2), NULL);
	nw_str = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	start = nw_str;
	s2_start = (char *)s2;
	if (NULL != nw_str)
	{
		while ('\0' != *s1)
			*(nw_str++) = *(s1++);
		while ('\0' != *s2)
			*(nw_str++) = *(s2++);
	}
	free(s2_start);
	return (start);
}

char	*ft_strjoin_f1_f2(char const *s1, char const *s2)
{
	char	*start;

	start = ft_strjoin(s1, s2);
	free((void *) s1);
	free((void *) s2);
	return (start);
}
