/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/21 03:26:36 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	load_noi_mode(t_core *shell)
{
	while (ft_getnextline(STDIN_FILENO, &shell->term.buffer))
	{
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			return (quit_shell(shell, EXIT_FAILURE, FALSE));
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
