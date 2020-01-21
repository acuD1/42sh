/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/16 16:51:55 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		load_noi_mode(t_core *shell)
{
	while (ft_getnextline(STDIN_FILENO, &shell->term.buffer))
	{
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			return (quit_shell(shell, EXIT_FAILURE, FALSE, NOI_MODE));
		free_prompt(shell);
	}
}

void		load_i_mode(t_core *shell)
{
	version(shell);
	init_cmd_line(shell, &shell->term); // Check return ?
	while (1)
	{
		if (init_prompt(shell) != SUCCESS)
			return ;
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			return (quit_shell(shell, EXIT_FAILURE, FALSE, I_MODE));
		save_history(&shell->term);
		free_prompt(shell);
	}
}
