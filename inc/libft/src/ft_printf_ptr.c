/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:20:34 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 11:23:18 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_printf_temp(size_t temp)
{
	char	*base;
	int		len;

	base = "0123456789abcdef";
	len = 1;
	if (temp >= 16)
	{
		len += ft_printf_temp(temp / 16);
		ft_putchar(base[temp % 16]);
	}
	else
		ft_putchar(base[temp]);
	return (len);
}

int	ft_putptr(void *ptr)
{
	size_t	temp;

	temp = (size_t)ptr;
	return (ft_putstr("0x") + ft_printf_temp(temp));
}
