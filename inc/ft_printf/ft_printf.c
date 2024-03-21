/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 19:57:58 by iostancu          #+#    #+#             */
/*   Updated: 2022/03/26 18:14:11 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	type_conversion(va_list ap, const char *frmt, int i)
{
	int	ret;

	ret = 0;
	if (frmt[i] == 'c')
		ret += ft_putchar(ap);
	if (frmt[i] == 'i' || frmt[i] == 'd')
		ret += ft_putnbr(ap);
	if (frmt[i] == 's')
		ret += ft_putstr(ap);
	if (frmt[i] == 'p')
		ret += ft_putnbrbase(ap);
	if (frmt[i] == 'u')
		ret += ft_unsignednbr(ap);
	if (frmt[i] == 'x')
		ret += ft_nbrbase_lu(ap, FALSE);
	if (frmt[i] == 'X')
		ret += ft_nbrbase_lu(ap, TRUE);
	if (frmt[i] == '%')
		ret += write(1, "%", 1);
	return (ret);
}

int	ft_printf(const char *frmt, ...)
{
	va_list	ap;
	int		i;
	int		ret;

	i = 0;
	ret = 0;
	va_start(ap, frmt);
	while (frmt[i])
	{
		if (frmt[i] == '%')
		{
			i++;
			ret += type_conversion(ap, frmt, i);
		}
		else
			ret += write(1, &frmt[i], 1);
		i++;
	}
	return (ret);
}
