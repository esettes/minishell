#include "../../inc/headers/minishell.h"

static void	out_handler(t_scmd *scmd, char *redirect, char *out_file)
{
	int	outfile;

	outfile = 0;
	if (scmd->out_f)
		free(scmd->out_f);
	scmd->out_f = ft_strdup(out_file);
	if ('>' == redirect[1])
	{
		scmd->append = TRUE;
		outfile = open(out_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	}
	else if ('\0' == redirect[1])
	{
		scmd->append = FALSE;
		outfile = open(out_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	close(outfile);
}

static int	heredoc_init(t_scmd *scmd, char *tok, size_t tok_len)
{
	int		heredoc;
	ssize_t core_read;
	char	buffer[BUFSIZ];

	core_read = 1;
	scmd->in_f = ft_strdup("tmp");
	heredoc = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	while (ZERO < core_read)
	{
		core_read = read(STDIN_FILENO, buffer, BUFSIZ);
		if (-1 == core_read)
			return (EXIT_FAILURE);
		buffer[core_read] = '\0';//maybe not necesary 
		if (ZERO == ft_strncmp(buffer, tok, tok_len))
			break;
		if (-1 == write(heredoc, buffer, core_read))
			return (EXIT_FAILURE);
	}
	close(heredoc);
	return (EXIT_SUCCESS);
}

static void	heredoc_handler(t_scmd *scmd, t_list *tokens)
{
	char	*tok;

	(void)scmd;
	if ('\0' != ((char *)tokens->content)[2])
		tok = tokens->content + 2;
	else
	{
		tok = tokens->next->content;
		tokens = tokens->next;
	}
	tokens = tokens->next;
	heredoc_init(scmd, tok, ft_strlen(tok));
}

static void	in_handler(t_scmd *scmd, t_list *tokens)
{
	if ('\0' == ((char *)(tokens->content))[1]) /*TODO*/
		scmd->in_f = ft_strdup(tokens->next->content);
	else if ('<' == ((char *)(tokens->content))[1])
		heredoc_handler(scmd, tokens);
	/* << TODO */
	/* MAYBE OPEN FILE AND DUP, IDK */
}

void	redirect_phase(t_scmd *scmd, t_list **tokens, int *i)
{
	while (*tokens && T_REDIRECT == val_get_type((*tokens)->content))
	{
		if (NULL == (*tokens)->next)
			exit(42);/* BAD FORMAT no file after redirection */
		if ('<' == *(char *)(*tokens)->content)
			in_handler(scmd, *tokens);
		else if ('>' == *(char *)(*tokens)->content)
			out_handler(scmd, (*tokens)->content, (*tokens)->next->content);
		(*tokens) = (*tokens)->next->next;
		*i -= 2;
	}
}
