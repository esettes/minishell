#include "../../inc/headers/minishell.h"

volatile int g_signal;

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

int	core_shell(char **envp)
{
	char	*buffer;
	char	*oldbuffer;
	t_cmd	*cmd;
	t_pipe	*p_data;
	struct sigaction	s0;
	char	*prompt;
	size_t	show_sig;

	 g_signal = 0;
	show_sig = 0;
	s0.sa_handler = &c_handler;
	s0.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &s0, NULL))
		return (ft_puterror("error: sigaction\n"), EXIT_FAILURE);
	if (enmask_signals())
		return (EXIT_FAILURE);
	buffer = ft_strdup("");
	oldbuffer = ft_strdup("");
	p_data = init_pipe_struct(envp);
	if (!p_data)
		return (EXIT_FAILURE);
	prompt = NULL;
  while(buffer)
	{
		//g_signal = 0;
		if (buffer)
		{
			free(buffer);
			buffer = (char *)NULL;
		}
		prompt = get_prompt(p_data);
		buffer = readline(prompt);
		free (prompt);
		if (!buffer)
			return (f_error());
		if (buffer && *buffer && ft_strncmp(buffer, oldbuffer, sizeof(oldbuffer)) != 0)
			add_history(buffer);
		if (show_sig == 1)
		{
			
			show_sig = 0;
			g_signal = 0;
			printf("show sig = 0 and g_signal: %d\n",  g_signal);
		}
		cmd = parser(buffer, p_data->envp_minish);
		if (NULL == cmd)
			continue ;
		if (ft_strncmp("", buffer, 1) == 0)
			continue ;
		free(oldbuffer);
		oldbuffer = (char *)NULL;
		oldbuffer = ft_strdup(buffer);
		
		if (f_pipex(p_data, cmd, envp))
			continue ;
		if (g_signal != 0 && show_sig == 0)
		{
			printf("show sig = 1 and g_signal: %d\n",  g_signal);
			show_sig = 1;
			continue ;
		}
		
		/*CONDICIONES DE SALIDA: señales*/
	}
	free(buffer);
	free(oldbuffer);
	// free(cmd->scmd);
	// free(cmd);
	free_cmd(&cmd);
	free(p_data->envp);
	free_memory((const char **)p_data->envp_minish, get_array_size(p_data->envp_minish));
	free(p_data);
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
