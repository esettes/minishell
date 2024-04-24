/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:20:37 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 11:23:34 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putstr(char *s)
{
	int	count;

	if (!s)
		return (0);
	count = 0;
	while (*s)
	{
		count += ft_putchar(*s);
		s++;
	}
	return (count);
}
