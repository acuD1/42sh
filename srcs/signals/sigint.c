/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:45:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/16 03:53:26 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

static void		erase_line(t_core *shell)
{
	if (shell->term.status == CMD_PROMPT)
	{
		while (shell->term.x_index < shell->term.width)
			move_right(shell->term.buffer, &(shell->term));
		ft_bzero(shell->term.buffer, BUFF_SIZE);
		write(2, "\n", 1);
		display_prompt(&(shell->term));
	}
	else if (shell->term.status == CMD_SUBPROMPT)
	{
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_strdup(shell->term.tmp_buff);
		save_history(&shell->term);
		ft_bzero(shell->term.buffer, BUFF_SIZE);
		ft_bzero(shell->term.tmp_buff, ft_strlen(shell->term.tmp_buff));
		ft_strdel(&(shell->term.tmp_buff));
		shell->term.status = CMD_PROMPT;
		write(2, "\n", 1);
		ft_strdel(&shell->term.prompt);
		get_prompt_value(shell, "PS1");
		display_prompt(&(shell->term));
	}
}

void			sigint_handler(int signum)
{
	t_core	*shell;

	shell = get_core(NULL);
	signal(SIGINT, sigint_handler);
	shell->status = 128 + signum;
	update_exit_status(shell);
	erase_line(shell);
}
