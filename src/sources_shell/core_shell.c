/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   core_shell.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iostancu <iostancu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/05 20:06:11 by iostancu          #+#    #+#             */
/*   Updated: 2024/04/16 00:35:21 by iostancu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_signal;

char	*get_prompt(t_pipe *data);
void	sig_interrupt(int signum);
void	sig_newentry(int signum);

static void	c_handler(int sig)
{
	//termina la readline y muestra otra entrada
	(void) sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

static void	bs_handler(int sig)
{

	(void) sig;
	printf("bs signal catch");
	exit (42);
}

static int	enmask_signals(void)
{
	static struct sigaction	s1;

	s1.sa_handler = &bs_handler;
	if (sigaction(SIGQUIT, &s1, NULL))
		return (ft_puterror("error: sigaction\n"), EXIT_FAILURE);
	// while (TRUE)
	// {
	// 	printf("Esperando por una señal\n");
	// 	sleep(2);
	// }
	return (EXIT_SUCCESS);
}

int manage_signactions(void)
{
	struct sigaction	s0;

	s0.sa_handler = &c_handler;
	s0.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &s0, NULL))
		return (ft_puterror("error: sigaction\n"), EXIT_FAILURE);
	if (enmask_signals())
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static void	free_all(t_cmd *cmd, t_pipe *p_data, t_buff *buff)
{
	free_cmd(&cmd);
	free(p_data->envp);
	free_memory((const char **)p_data->envp_minish, get_array_size(p_data->envp_minish));
	free(p_data);
	free(buff->buffer);
	free(buff->oldbuffer);
}

int	core_shell(char **envp)
{
	t_buff	b;
	t_cmd	*cmd;
	t_pipe	*p_data;
	char	*prompt;

	g_signal = 0;
	b.buffer = ft_strdup("");
	b.oldbuffer = ft_strdup("");
	p_data = init_pipe_struct(envp);
	if (!p_data)
		return (EXIT_FAILURE);
	prompt = NULL;
	while(b.buffer)
	{
		if (b.buffer)
		{
			free(b.buffer);
			b.buffer = (char *)NULL;
		}
		prompt = get_prompt(p_data);
		b.buffer = readline(prompt);
		free (prompt);
		if (!b.buffer)
			return (f_error());
		if (b.buffer && *b.buffer && f_strict_strncmp(b.buffer,
			b.oldbuffer, sizeof(b.oldbuffer)) != 0)
			add_history(b.buffer);
		cmd = parser(b.buffer, p_data->envp_minish);
		if (NULL == cmd)
			continue ;
		if (ft_strncmp("", b.buffer, 1) == 0)
			continue ;
		free(b.oldbuffer);
		b.oldbuffer = (char *)NULL;
		b.oldbuffer = ft_strdup(b.buffer);
		
		f_pipex(p_data, cmd, envp);
	}
	free_all(cmd, p_data, &b);
	return (EXIT_SUCCESS);
}

char	*get_prompt(t_pipe *data)
{
	t_prompt	prompt;

	prompt.home_substr = ft_substr(getcwd(NULL, 0), f_strlen(get_env_var_value(data->envp_minish, "HOME")),
						f_strlen(getcwd(NULL, 0)));
	prompt.curr_dir = f_strjoin(prompt.home_substr, " > ");
	if (f_strlen(prompt.curr_dir) <= 3)
	{
		free (prompt.curr_dir);
		prompt.curr_dir = f_strjoin(getcwd(NULL, 0), " > ");
	}
	prompt.usr = f_strjoin(getenv("USER"), " in ");
	prompt.join_usr_color = f_strjoin(GREEN_, prompt.usr);
	prompt.join_usr_curr_dir = f_strjoin(prompt.join_usr_color, prompt.curr_dir);
	prompt.prompt = f_strjoin(prompt.join_usr_curr_dir, RESET_);
	free(prompt.curr_dir);
	free(prompt.usr);
	free(prompt.join_usr_color);
	free(prompt.join_usr_curr_dir);
	free(prompt.home_substr);
	return (prompt.prompt);
}

void	sig_interrupt(int signum)
{
	(void)signum;
	ft_putstrc_fd(YELLOW_, "Caught interruption...\n", 1);
	exit(1);
}

void	sig_newentry(int signum)
{
	(void)signum;
	ft_putstrc_fd(RESET_, "^C\n", 1);
}
