/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   yacc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: antosanc <antosanc@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/12 16:58:44 by antosanc          #+#    #+#             */
/*   Updated: 2024/04/12 17:54:29 by antosanc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*Aqui la idea principal es añadir los comandos a la estructura t_cmd, para ello hay que contar argumentos
crear las estructuras suficientes para albergar todos los comandos y meterlos en t_scmd cada comando simple, 
en este punto hay que controlar heredoc. En teoria, si heredoc usa variables de entorno $HOME dentro de el
hay que expandirlas*/

#include "../../inc/headers/minishell.h"

t_cmd	*yacc_tony(t_cmd *cmd, t_list *tokens)
{
	
}