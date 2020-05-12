/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:45:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/05/12 12:17:56 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>
#include <unistd.h>

static void	erase_line(t_core *shell)
{
	if (shell->term.status == CMD_PROMPT)
	{
		shell->term.ctrl_c = 1;
		goto_prompt(&shell->term);
		ft_strdel(&shell->term.buffer);
		ft_strdel(&shell->term.tmp_buff);
		shell->term.buffer = ft_memalloc(BUFF_SIZE + 1);
	}
	else if (shell->term.status == CMD_SUBPROMPT)
	{
		shell->ctrl_c = 1;
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_strdup(shell->term.tmp_buff);
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE + 1);
		shell->term.status = CMD_PROMPT;
		ft_strdel(&shell->sub.keys);
		ft_strdel(&shell->term.prompt);
		ft_strdel(&(shell->term.tmp_buff));
		shell->job_list = NULL;
	}
}

void		sigint_handler(int signum)
{
	t_core	*shell;

	shell = get_core(NULL);
	signal(SIGINT, sigint_handler);
	shell->status = 128 + signum;
	ft_dprintf(STDERR_FILENO, "^C\n");
	update_exit_status(shell);
	erase_line(shell);
}
