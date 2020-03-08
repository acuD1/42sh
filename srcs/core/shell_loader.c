/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 14:45:22 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

void	load_noi_mode(t_core *shell)
{
	int		i;

	while (ft_getnextline(STDIN_FILENO, &shell->term.buffer))
	{
		i = 0;
		while (shell->term.buffer[i])
		{
			if (shell->term.buffer[i] < 0)
			{
				ft_dprintf(STDERR_FILENO,
					"42sh: syntax error: invalid token\n");
				quit_shell(shell, 2, FALSE);
			}
			i++;
		}
		lexer_parser_analyzer(shell);
		task_master(shell);
		ft_bzero(shell->term.buffer, ft_strlen(shell->term.buffer));
		free_prompt(shell);
	}
	quit_shell(shell, shell->status, FALSE);
}

void	load_i_mode(t_core *shell)
{
	init_cmd_line(shell, &shell->term);
	while (1)
	{
		if (init_prompt(shell) != SUCCESS)
			return ;
		lexer_parser_analyzer(shell);
		do_job_notification(shell, shell->launched_jobs);
		if (task_master(shell) != SUCCESS)
			return (quit_shell(shell, EXIT_FAILURE, FALSE));
		save_history(&shell->term);
		free_prompt(shell);
	}
}
