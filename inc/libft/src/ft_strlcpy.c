/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:47:39 by antosanc          #+#    #+#             */
/*   Updated: 2023/09/29 14:47:42 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	num;

	i = 0;
	while (src[i])
		i++;
	num = 0;
	if (n)
	{
		while (src[num] && num < n - 1)
		{
			dest[num] = src[num];
			num++;
		}
		dest[num] = '\0';
	}
	return (i);
}
