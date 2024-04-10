/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 12:18:19 by uherrero          #+#    #+#             */
/*   Updated: 2023/12/14 21:37:52 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"
#include <stdio.h>

size_t	ft_strlen(const char *s)
{
	register size_t	len;

	len = ZERO;
	while (s[len])
		len++;
	return (len);
}
