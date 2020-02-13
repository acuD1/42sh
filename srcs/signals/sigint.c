/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sigint.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 16:45:16 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/13 18:15:00 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <signal.h>

static void		kill_processes(int signum, t_core *shell)
{
	t_lst	*ptr;

	ptr = shell->running_process->next;
	kill(((t_process*)shell->running_process->content)->pid, signum);
	if (ptr && ((t_process*)ptr->content)->type == P_PIPE)
	{
		while (ptr && ((t_process*)ptr->content)->type == P_PIPE)
		{
			kill(((t_process*)ptr->content)->pid, signum);
			ptr = ptr->next;
		}
		kill(((t_process*)ptr->content)->pid, signum);
	}
	shell->running_process = NULL;
}

static void		erase_line(t_core *shell)
{
	if (shell->term.status == CMD_PROMPT)
	{
		while (shell->term.x_index < shell->term.width)
			move_right(shell->term.buffer, &(shell->term));
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
		ft_putchar('\n');
		display_prompt(&(shell->term));
	}
	else if (shell->term.status == CMD_SUBPROMPT)
	{
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_strdup(shell->term.tmp_buff);
		save_history(&shell->term);
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
		shell->term.status = CMD_PROMPT;
		ft_putchar('\n');
		ft_strdel(&shell->term.prompt);
		get_prompt_value(shell, "PS1");
		display_prompt(&(shell->term));
	}
}

void			sigint_handler(int signum)
{
	t_core	*shell;

	(void)signum;
	shell = get_core(NULL);
	signal(SIGINT, sigint_handler);
	if (shell->running_process != NULL)
	{
		kill_processes(signum, shell);
		write(2, "\n", 1);
	}
	else
		erase_line(shell);
}
