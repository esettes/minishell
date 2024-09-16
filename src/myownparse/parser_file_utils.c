#include "minishell.h"

int	open_files(t_pipe *data, char *file_name, char red)
{
	if ((red == LESS_THAN || red == HERE_DOC) && *file_name)
	{
		if (data->infile)
			(close(data->infile), data->infile = 0);
		if (red == LESS_THAN)
			data->infile = open(file_name, O_RDONLY);
		else
			here_doc(data, file_name);
	}
	else if ((red == MORE_THAN || red == APPEND) && *file_name)
	{
		if (data->outfile)
			(close(data->outfile), data->outfile = 0);
		if (red == MORE_THAN)
			data->outfile = open(file_name, O_TRUNC | O_CREAT | O_WRONLY, 0644);
		else
			data->outfile = open(file_name, O_APPEND | O_CREAT | O_WRONLY, 0644);
	}
	else if (!*file_name)
		print_err_msg(red);
	if (data->infile == -1 || data->outfile == -1)
		return (ft_printf("minishell: "), data->outfile = 0, data->infile = 0,
			perror(file_name), -1);
	return (0);
}

char	get_redir_type(char *cmd_line, int i)
{
	char	red;

	red = cmd_line[i - 1];
	if (cmd_line[i] == MORE_THAN && cmd_line[i] == red)
		red = APPEND;
	else if (cmd_line[i] == LESS_THAN && cmd_line[i] == red)
		red = HERE_DOC;
	return (red);
}

int	manage_line(t_pipe *data, char *cmd_line, int i)
{
	char	red;
	int		j;
	char	*name;

	j = i++;
	red = get_redir_type(cmd_line, i);
	if (red == APPEND || red == HERE_DOC)
		i++;
	while (ft_isblank(cmd_line[i]))
		i++;
	ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
	i = i - (i - j);
	while (!ft_isblank(cmd_line[i]) && cmd_line[i]
		&& (cmd_line[i] != MORE_THAN && cmd_line[i] != LESS_THAN))
		i++;
	if (i == j)
		return (print_err_msg(red), -1);
	name = ft_substr(cmd_line, j, i - j);
	if (open_files(data, reset_pipes(name), red) == -1)
		return (free(name), -1);
	free(name);
	ft_memmove(&cmd_line[j], &cmd_line[i], ft_strlen(cmd_line) - i + 1);
	return (i = i - (i - j));
}

int	redir_files(t_pipe *data, char *cmd_line)
{
	int		i;

	i = 0;
	while (cmd_line[i])
	{
		while (cmd_line[i] == MORE_THAN || cmd_line[i] == LESS_THAN)
		{
			i = manage_line(data, cmd_line, i);
			if (i == -1)
				return (0);
		}
		i++;
	}
	return (1);
}

char	*f_find_path(char *cmd, t_list **env)
{
	int		i;
	char	**split_path;
	char	*path;
	char	*slashed_cmd;
	char	value_buf[BUF_SIZE];

	if (!cmd)
		return (0);
	if (!access(cmd, 0) && ft_strchr(cmd, '/'))
		return (ft_strdup(cmd));
	split_path = ft_split(ft_getenv(env, "PATH", value_buf), ':');
	if (!split_path)
		return (0);
	i = -1;
	while (split_path[++i])
	{
		slashed_cmd = ft_strjoin(split_path[i], "/");
		path = ft_strjoin(slashed_cmd, cmd);
		free(slashed_cmd);
		if (access(path, 0) == 0)
			return (free_dp(split_path), path);
		free(path);
	}
	free_dp(split_path);
	return (0);
}
