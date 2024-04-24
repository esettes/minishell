/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_error.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ubuntu <ubuntu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/12 16:58:16 by antosanc          #+#    #+#             */
/*   Updated: 2024/02/26 21:21:06 by ubuntu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/libft.h"

void	ft_print_error(const char *error)
{
	ft_printf("%sError:%s %s\n", RED, CLEAR, error);
	exit(EXIT_FAILURE);
}
