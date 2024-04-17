/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 19:53:41 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/17 23:16:55 by iostancu         ###   ########.fr       */
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
