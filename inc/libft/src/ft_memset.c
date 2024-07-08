/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/11 18:50:57 by antosanc          #+#    #+#             */
/*   Updated: 2023/09/11 18:57:49 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t	num;

	num = 0;
	while (num < n)
	{
		*((unsigned char *)s + num) = c;
		num++;
	}
	return (s);
}
