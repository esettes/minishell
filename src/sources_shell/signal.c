#include "minishell.h"

static void	bs_handler(int sig)
{
	(void) sig;
}

static void	c_handler(int sig)
{
	(void) sig;
	write(1, "\n", 1);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
    g_signal = 130;
}

int manage_signactions(void)
{
	struct sigaction	s0;

	s0.sa_handler = &c_handler;
	s0.sa_flags = SA_RESTART;
	if (sigaction(SIGINT, &s0, NULL))
		return (ft_puterror("error: sigaction\n"), EXIT_FAILURE);
	if (signal(SIGQUIT, bs_handler))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

//falta funcion para no mostrar ^\ por la entrada

