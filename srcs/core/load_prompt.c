/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/11 16:00:48 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Ok so here we have our prompt. this is a basic one from minishell.
**	The current format is mainly for testing purpose.
**	free_prompt is our main fonction that free almost everythings
**	wiches are globals variables, such as tokens, env list etc...
*/

void			load_prompt(t_core *shell)
{
	version(shell);
	init_cmd_line(shell, &shell->term);
	while (1)
	{
		init_prompt(shell);
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			quit_shell(shell, EXIT_FAILURE, FALSE) ;
		save_history(&shell->term);
		free_prompt(shell);
	}
}
