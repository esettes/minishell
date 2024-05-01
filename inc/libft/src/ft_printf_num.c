/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_num.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:20:29 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 11:23:02 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_putnbr(int n)
{
	long	num;
	int		len;

	num = n;
	len = 0;
	if (num < 0)
	{
		num *= -1;
		len += ft_putchar('-');
	}
	if (num > 9)
	{
		len += ft_putnbr((num / 10));
		len += ft_putchar(((num % 10) + '0'));
	}
	else
		len += ft_putchar((num + '0'));
	return (len);
}

int	ft_putnbr_unsigned(unsigned int n)
{
	long int	num;
	int			len;

	num = n;
	len = 0;
	if (num > 9)
	{
		len += ft_putnbr_unsigned(num / 10);
		len += ft_putchar((num % 10) + '0');
	}
	else
		len += ft_putchar((num % 10) + '0');
	return (len);
}
