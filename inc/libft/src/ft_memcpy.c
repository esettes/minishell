/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:46:53 by antosanc          #+#    #+#             */
/*   Updated: 2023/09/29 14:46:56 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	num;

	if (src == dest)
		return (dest);
	num = 0;
	while (num < n)
	{
		*((unsigned char *)dest + num) = *((unsigned char *)src + num);
		num++;
	}
	return (dest);
}
