/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:58:29 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/06 11:03:02 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <signal.h>

static u_int8_t	heredoc_error(const char *key)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: warning: here-document delimited by eof (wanted `%s')\n", key);
	return (TRUE);
}

static u_int8_t	check_key(t_core *shell, const char *key)
{
	if (read_multiline(shell) == FALSE)
	{
		if (shell->term.status == CMD_DONE)
			return (heredoc_error(key));
		if (ft_strcmp(shell->term.buffer, key))
		{
			shell->term.buffer = ft_strjoinf(shell->term.tmp_buff,
														shell->term.buffer, 2);
			shell->term.buffer = ft_strjoinf(shell->term.buffer, NEW_LINE, 1);
			ft_strdel(&shell->term.tmp_buff);
			shell->term.tmp_buff = ft_strdup(shell->term.buffer);
			return (FALSE);
		}
		else
			return (TRUE);
	}
	return (FALSE);
}

u_int8_t		read_multiline(t_core *shell)
{
	char	buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE + 1);
	sigint_special_handler();
	while (shell->term.status == CMD_SUBPROMPT
			&& read(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (check_caps(buff, shell) == TRUE)
			ft_bzero(buff, READ_SIZE + 1);
		else
		{
			signal(SIGINT, sigint_handler);
			return (FALSE);
		}
	}
	signal(SIGINT, sigint_handler);
	return (TRUE);
}

static char		*stock_value(t_core *shell)
{
	char	*value;
	char	*buffer;
	size_t	i;

	value = NULL;
	buffer = ft_strdup(shell->term.tmp_buff);
	ft_strdel(&shell->term.tmp_buff);
	i = ft_strlen_to(buffer, NEW_LINE[0]);
	shell->term.status = CMD_DONE;
	value = ft_strsub(buffer, (unsigned int)i + 1, ft_strlen(buffer) - i);
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_strsub(buffer, 0, i);
	ft_strdel(&buffer);
	reset_config(shell);
	return (value);
}

char			*load_heredoc(t_core *shell, const char *key)
{
	set_termconfig(shell);
	shell->heredoc = 0;
	shell->term.buffer = ft_strjoinf(shell->term.buffer, NEW_LINE, 1);
	shell->term.tmp_buff = ft_strdup(shell->term.buffer);
	shell->term.status = CMD_SUBPROMPT;
	get_prompt_value(shell, "PS2");
	while (TRUE && shell->term.status == CMD_SUBPROMPT)
	{
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE + 1);
		display_subprompt(&shell->term);
		if (check_key(shell, key) == FALSE)
			continue ;
		else if (*shell->term.prompt
			|| (!*shell->term.prompt && shell->term.buffer))
			break ;
		if (shell->term.status == CMD_PROMPT)
			return (NULL);
	}
	if (shell->term.tmp_buff == NULL)
		return (ft_strdup(key));
	return (stock_value(shell));
}
