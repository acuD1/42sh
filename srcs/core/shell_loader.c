/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_loader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/13 15:23:52 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t		load_noi_mode(t_core *shell)
{
	while (ft_getnextline(STDIN_FILENO, &shell->term.buffer))
	{
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			quit_shell(shell, EXIT_FAILURE, FALSE, NOI_MODE);
		free_prompt(shell);
	}
	return (SUCCESS);
}

u_int8_t		shell_loader(t_core *shell)
{
	if (shell->mode & NOI_MODE)
		return (load_noi_mode(shell));
	version(shell);
	init_cmd_line(shell, &shell->term); // Check return ?
	while (shell->mode & I_MODE)
	{
		if (shell->mode & EXIT)
			break ;
		init_prompt(shell);
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			quit_shell(shell, EXIT_FAILURE, FALSE, I_MODE);
		save_history(&shell->term);
		free_prompt(shell);
	}
	return (SUCCESS);
}
