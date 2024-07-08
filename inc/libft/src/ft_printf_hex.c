/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:20:25 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 11:22:53 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_print_hex(unsigned int num, char *base)
{
	int	len;

	len = 0;
	if (num >= 16)
	{
		len += ft_print_hex((num / 16), base);
		len += ft_putchar(base[num % 16]);
	}
	else
		len += ft_putchar(base[num]);
	return (len);
}

int	ft_putnbr_hex(unsigned int num, char c)
{
	char	*base_upper;
	char	*base_lower;

	base_upper = "0123456789ABCDEF";
	base_lower = "0123456789abcdef";
	if (c == 'x')
		return (ft_print_hex(num, base_lower));
	if (c == 'X')
		return (ft_print_hex(num, base_upper));
	return (0);
}
