/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:53:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/02/03 20:58:45 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	ft_putstrc_fd(char *color, char *s, int fd)
{
	if (!s || fd < 0)
		return ;
	while (*color)
		write(fd, color++, 1);
	while (*s)
		write (fd, s++, 1);
	color = "\x1b[0m";
}

char	*f_strdup(const char *s1)
{
	size_t	i;
	size_t	len;
	char	*cpy;

	i = 0;
	len = f_strlen(s1);
	cpy = (char *)malloc(f_strlen((char *)s1) + 1);
	if (cpy == NULL)
		return (NULL);
	while (i < len)
	{
		cpy[i] = s1[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

int	f_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	if (n == 0)
		return (0);
	while (str1[i] != '\0' || str2[i] != '\0')
	{
		if (i == n - 1 || str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int	f_strict_strncmp(const char *s1, const char *s2, size_t n)
{
	if (f_strncmp(s1, s2, n) == 0)
	{
		if (f_strlen(s1) != f_strlen(s2))
			return (1);
	}
	else
		return (1);
	return (0);
}

char	*f_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	res = (char *)malloc(f_strlen((char *)s1) + (f_strlen((char *)s2)) + 1);
	if (!res)
		return (NULL);
	while (s1[i])
		res[i++] = (char)s1[j++];
	j = 0;
	while (s2[j])
		res[i++] = s2[j++];
	res[i] = '\0';
	return (res);
}

size_t	f_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i])
		i++;
	return (i);
}

void	*f_memset(void *b, int c, size_t len)
{
	unsigned char	*p;

	p = b;
	while (len-- > 0)
		*p++ = (char)c;
	return (b);
}

void	*f_memmove(void *dst, const void *src, size_t len)
{
	const unsigned char	*s;
	unsigned char		*d;
	size_t				i;

	s = (const unsigned char *)src;
	d = (unsigned char *)dst;
	i = 0;
	if (NULL == dst && NULL == src)
		return (dst);
	if (d > s)
	{
		while (len-- > 0)
			d[len] = s[len];
	}
	else
	{
		while (i < len)
		{
			d[i] = s[i];
			i++;
		}
	}
	return (dst);
}

void	f_bzero(void *s, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
		*(char *)(s + i++) = 0;
}
