/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:20:07 by antosanc          #+#    #+#             */
/*   Updated: 2023/11/25 11:22:27 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

static int	ft_valid_format(char str)
{
	char	*format;

	format = "cspdiuxX%";
	while (*format)
	{
		if (str == *format)
			return (1);
		format++;
	}
	return (0);
}

static int	ft_format_str(char str, va_list args)
{
	if (str == 'c')
		return (ft_putchar((char)va_arg(args, int)));
	if (str == 's')
		return (ft_putstr(va_arg(args, char *)));
	if (str == 'p')
		return (ft_putptr(va_arg(args, void *)));
	if (str == 'd' || str == 'i')
		return (ft_putnbr(va_arg(args, int)));
	if (str == 'u')
		return (ft_putnbr_unsigned(va_arg(args, unsigned int)));
	if (str == 'x' || str == 'X')
		return (ft_putnbr_hex(va_arg(args, unsigned int), str));
	if (str == '%')
		return (ft_putchar('%'));
	return (0);
}

int	ft_printf(char const *str, ...)
{
	va_list	args;
	char	*temp;
	int		count;

	va_start(args, str);
	temp = (char *)str;
	count = 0;
	while (*temp)
	{
		if (*temp == '%' && (ft_valid_format(*(temp + 1)) == 1))
			count += ft_format_str(*(++temp), args);
		else
			count += ft_putchar(*temp);
		temp++;
	}
	va_end(args);
	return (count);
}
