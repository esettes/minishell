/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_base.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 17:57:05 by iostancu          #+#    #+#             */
/*   Updated: 2022/03/26 17:59:44 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_pnb(int ret, unsigned long int n)
{
	if (n >= 16)
	{
		ret = ft_pnb(ret, n / 16);
		ret += write(1, &HEX[n % 16], 1);
	}
	else
		ret += write(1, &HEX[n % 16], 1);
	return (ret);
}

int	ft_pnb_up(unsigned int ret, unsigned int n)
{
	if (n >= 16)
	{
		ret = ft_pnb_up(ret, n / 16);
		ret += write(1, &UPHEX[n % 16], 1);
	}
	else
		ret += write(1, &UPHEX[n % 16], 1);
	return (ret);
}

unsigned int	ft_nbrbase_lu(va_list ap, int isup)
{
	unsigned int	n;
	int				ret;

	n = (unsigned int)va_arg(ap, void *);
	ret = 0;
	n == 0 && (ret += write(1, "0", 1));
	if (isup == FALSE)
		n != 0 && (ret = ft_pnb(ret, n));
	else
		n != 0 && (ret = ft_pnb_up(ret, n));
	return (ret);
}

int	ft_putnbrbase(va_list ap)
{
	unsigned long int	n;
	int					ret;

	n = (unsigned long int)va_arg(ap, void *);
	ret = 0;
	ret += write(1, "0x", 2);
	n == 0 && (ret += write(1, "0", 1));
	n != 0 && (ret = ft_pnb(ret, n));
	return (ret);
}
