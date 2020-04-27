/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/23 16:55:09 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>
#include <stdlib.h>

void	load_noi_mode(t_core *shell)
{
	size_t	i;

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
		reset_config(shell);
		lexer_parser_analyzer(shell);
		do_job_notification(shell, shell->launched_jobs, TRUE);
		task_master(shell);
		save_history(&shell->term);
		free_prompt(shell);
	}
}
