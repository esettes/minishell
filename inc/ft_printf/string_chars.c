/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_chars.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:56:42 by iostancu          #+#    #+#             */
/*   Updated: 2022/03/26 17:58:59 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putchar_c(char c)
{
	int	ret;

	ret = 0;
	ret = write(1, &c, 1);
	return (ret);
}

int	ft_putchar(va_list ap)
{
	int	a;
	int	ret;

	a = va_arg(ap, int);
	ret = ft_putchar_c(a);
	return (ret);
}

int	ft_putstr(va_list ap)
{
	char	*str;
	int		ret;

	str = va_arg(ap, char *);
	ret = 0;
	if (!str)
		ret += write(1, "(null)", 6);
	else
		while (*str)
			ret += write(1, str++, 1);
	return (ret);
}
