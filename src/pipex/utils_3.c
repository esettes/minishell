/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: settes <settes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 20:38:33 by antosanc          #+#    #+#             */
/*   Updated: 2024/09/06 17:14:55 by settes           ###   ########.fr       */
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

static int	f_isblank(int c)
{
	if (c == 11 || c == 13 || c == 32)
		return (c);
	return (0);
}

int	is_empty_line(char *s)
{
	int	i;

	if (!ft_strncmp(s, "\"\"\0", 3) || !ft_strncmp(s, "''\0", 3))
		return (1);
	i = -1;
	while (s[++i])
	{
		if (!f_isblank(s[i]))
			return (0);
	}
	return (1);
}
