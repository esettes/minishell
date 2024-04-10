/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 19:27:39 by iostancu          #+#    #+#             */
/*   Updated: 2024/03/13 23:42:41 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

size_t	var_lenght(char *var);

int	is_correct_env_variable(char *var, char *cmd)
{
	size_t	i;
	size_t	count;
	int		ret;

	i = 0;
	ret = TRUE;
	count = 0;
	if (!(ft_isalpha(var[0]) || var[0] == '_'))
		ret = FALSE;
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalnum(var[i]) && var[i] != '_')
			ret = FALSE;
		i++;
	}
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (ft_isdigit(var[i]))
			count++;
		i++;
	}
	if (count == var_lenght(var))
		ret = FALSE;
	if (var[ft_strlen(var) - 1] == '='
		&& f_strncmp(cmd, "unset", f_strlen(cmd)) == 0)
		ret = FALSE;
	if (ret == FALSE)
	{
		ft_putstrc_fd(RED_, "minishell: ", 2);
		ft_putstrc_fd(RED_, cmd, 2);
		ft_putstrc_fd(RED_, ": `", 2);
		ft_putstrc_fd(RED_, var, 2);
		ft_putstrc_fd(RED_, "': not a valid identifier\n", 2);
		g_signal = 1;
		return (FALSE);
	}
	return (TRUE);
}

int	change_var_value(char **envp_minish, char *raw_variable)
{
	int		i;
	char	*var;
	int		envp_size;

	i = 0;
	var = get_env_variable(raw_variable);
	envp_size = get_array_size(envp_minish);
	if (!var)
		return (EXIT_SUCCESS);
	while (i < envp_size)
	{
		if (f_strncmp(envp_minish[i], var, f_strlen(var)) == 0)
		{
			free(envp_minish[i]);
			envp_minish[i] = f_strdup(raw_variable);
			free(var);
			free(raw_variable);
			return (EXIT_SUCCESS);
		}
		i++;
	}
	free(var);
	free(raw_variable);
	return (EXIT_SUCCESS);
}

char	*get_env_var_value(t_pipe *data, char *var)
{
	size_t	i;

	i = 0;
	while (data->envp_minish[i])
	{
		if (f_strncmp(data->envp_minish[i], var, f_strlen(var)) == 0)
			return (data->envp_minish[i] + f_strlen(var) + 1);
		i++;
	}
	return (NULL);
}

size_t	var_lenght(char *var)
{
	size_t	i;

	i = 0;
	while (var[i] && var[i] != '=')
		i++;
	return (i);
}
