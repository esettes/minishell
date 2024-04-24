/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:52:26 by antosanc          #+#    #+#             */
/*   Updated: 2023/09/29 17:08:26 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

static	int	ft_intlen(int n)
{
	int			cont;
	long long	num;

	num = n;
	cont = 0;
	if (num == 0)
		return (1);
	if (num < 0)
		cont++;
	while (num != 0)
	{
		num = num / 10;
		cont++;
	}
	return (cont);
}

static	char	*ft_intrev(int n, char *array, int len)
{
	long long	num;
	int			is_neg;

	num = n;
	is_neg = 0;
	array[len] = '\0';
	if (num < 0)
	{
		array[0] = '-';
		num *= -1;
		is_neg = 1;
	}
	while (len > is_neg)
	{
		len--;
		if (num > 9)
			array[len] = (num % 10) + '0';
		else
			array[len] = num + '0';
		num = num / 10;
	}
	return (array);
}

char	*ft_itoa(int n)
{
	char	*array;

	array = (char *)malloc(ft_intlen(n) + 1);
	if (array == 0)
		return (0);
	return (ft_intrev(n, array, ft_intlen(n)));
}
