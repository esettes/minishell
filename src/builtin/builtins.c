#include "minishell.h"

void	exec_pwd(void)
{
	char	abs_path[100000];

	ft_putstr_fd(getcwd(abs_path, sizeof(abs_path)), STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
}

int	exec_cd(char **cmd)
{
	int	status;

	status = 0;
	if (!cmd[1])
		status = f_perror(chdir(getenv("HOME")), "cd");
	else
		status = f_perror(chdir(cmd[1]), "cd");
	if (status)
		return (1);
	return (0);
}

void	exec_echo(char **word)
{
	int	i;

	i = 1;
	if (!word[1])
	{
		write(STDOUT_FILENO, "\n", 1);
		return ;
	}
	if (!ft_strncmp(word[1], "-n\0", 3))
		i++;
	while (word[i])
	{
		if (ft_strncmp(word[i], "-n\0", 3))
		{
			ft_putstr_fd(word[i], STDOUT_FILENO);
			if (word[i + 1])
				ft_putchar_fd(' ', STDOUT_FILENO);
		}
		i++;
	}
	if (ft_strncmp(word[1], "-n\0", 3))
		ft_putchar_fd('\n', STDOUT_FILENO);
}
