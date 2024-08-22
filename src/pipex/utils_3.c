/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:38:33 by antosanc          #+#    #+#             */
/*   Updated: 2024/08/23 00:15:00 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	create_simple_envp(t_pipe *data)
{
	char	*cwd;

	cwd = getcwd(NULL, 0);
	data->env_mini = create_new_var(data,
		"PATH=/usr/local/sbin:/usr/local/bin:/usr/sbin:"
			"/usr/bin:/sbin:/bin:/home/ubuntu/.local/bin");
	data->env_mini = create_new_var(data, "PWD=");
	change_var_value(data->env_mini, f_strjoin("PWD=", cwd));
	free(cwd);
}