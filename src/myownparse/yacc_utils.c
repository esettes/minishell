/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yacc_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 18:19:47 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/12 18:33:00 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/headers/minishell.h"

int	count_cmd(t_list *tokens)
{
	int	len;

	len = 1;
	while(tokens)
	{
		if (((char *)tokens->content)[0] == '|')
			len++;
		tokens = tokens->next;
	}
	return (len );
}