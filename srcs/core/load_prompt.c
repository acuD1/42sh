/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/13 11:08:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			load_prompt(t_core *shell)
{
	version(shell);
	init_cmd_line(shell, &shell->term);
	while (1)
	{
		init_prompt(shell);
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			quit_shell(shell, EXIT_FAILURE, FALSE);
		save_history(&shell->term);
		free_prompt(shell);
	}
}
