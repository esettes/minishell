/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_nbr.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:56:36 by iostancu          #+#    #+#             */
/*   Updated: 2022/03/26 17:56:37 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

long int	ptnb(long int nb, long int ret)
{
	char	s;

	if (nb < 0)
	{
		ret += write(1, "-", 1);
		nb *= -1;
	}
	if (nb > 9)
	{
		ret = ptnb(nb / 10, ret);
		ret = ptnb(nb % 10, ret);
	}
	else
	{
		s = nb + '0';
		ret += write(1, &s, 1);
	}
	return (ret);
}

unsigned int	ft_unsignednbr(va_list ap)
{
	unsigned int		nb;
	unsigned int		ret;

	nb = va_arg(ap, unsigned int);
	ret = 0;
	if (nb >= 0 && nb <= UINT_MAX)
		ret = ptnb(nb, ret);
	return (ret);
}

int	ft_putnbr(va_list ap)
{
	int		nb;
	int		ret;

	nb = va_arg(ap, int);
	ret = 0;
	if (nb >= -2147483648 && nb <= 2147483647)
	{
		if (nb == INT_MIN)
		{
			ret += write (1, "-2147483648", 11);
			return (ret);
		}
		ret = ptnb(nb, ret);
	}
	return (ret);
}
