/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:45:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/05 14:45:26 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>
/*  */
/* #include <fcntl.h> */
/* static void		debugg(const char *path, t_core *shell) */
/* { */
/* 	int			fd; */
/*  */
/* 	fd = open(path, O_WRONLY); */
/* 	ft_dprintf(fd, "research[%d] x[%d] xi[%d] y[%d], [%s]\n", shell->term.research, shell->term.x, shell->term.x_index, shell->term.y, shell->term.buffer); */
/*  */
/* } */

static void		erase_line(t_core *shell)
{
	if (shell->term.status == CMD_PROMPT)
	{
		goto_prompt(&shell->term);
		ft_strdel(&shell->term.buffer);
		ft_strdel(&shell->term.tmp_buff);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
	}
	else if (shell->term.status == CMD_SUBPROMPT)
	{
		if (shell->heredoc)
			shell->heredoc = 0;
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_strdup(shell->term.tmp_buff);
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
		shell->term.status = CMD_PROMPT;
		ft_strdel(&shell->term.prompt);
		get_prompt_value(shell, "PS1");
		display_prompt(&(shell->term));
		shell->job_list = NULL;
	}
}

void			sigint_handler(int signum)
{
	t_core	*shell;

	shell = get_core(NULL);
	signal(SIGINT, sigint_handler);
	shell->status = 128 + signum;
	ft_dprintf(STDERR_FILENO, "^C\n");
	update_exit_status(shell);
	erase_line(shell);
}
