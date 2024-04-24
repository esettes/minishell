/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/29 14:47:55 by antosanc          #+#    #+#             */
/*   Updated: 2023/09/29 14:47:58 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	num;

	num = ft_strlen(s);
	while (num >= 0)
	{
		if (s[num] == (char)c)
			return ((char *)&s[num]);
		num--;
	}
	return (0);
}
