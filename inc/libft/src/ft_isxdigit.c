/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isxdigit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 19:41:47 by uliherre          #+#    #+#             */
/*   Updated: 2024/09/16 18:36:52 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

int	ft_isxdigit(int c)
{
	if ((unsigned)c - '0' < 10 || (unsigned)c - 'a' < 6
		|| (unsigned)c - 'A' < 6)
		return (TRUE);
	return (FALSE);
}
