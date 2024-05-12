/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:47:35 by antosanc          #+#    #+#             */
/*   Updated: 2023/09/29 14:47:38 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;
	size_t	num;

	if (n == 0)
		return (ft_strlen(src));
	if (n <= ft_strlen(dest))
		num = n + ft_strlen(src);
	else
		num = ft_strlen(src) + ft_strlen(dest);
	i = 0;
	j = 0;
	while (dest[i])
		i++;
	while (src[j] && i < n - 1)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';
	return (num);
}
