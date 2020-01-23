/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/23 12:46:13 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Ok so here we have our prompt. this is a basic one from minishell.
**	The current format is mainly for testing purpose.
**	free_prompt is our main fonction that free almost everythings
**	wiches are globals variables, such as tokens, env list etc...
*/

// https://linuxconfig.org/bash-prompt-basics

/*
**	TO DO:
*/

void			load_prompt(t_core *shell)
{
	credit(shell);
	init_cmd_line(shell, &shell->term);
	while (1)
	{
		init_prompt(shell);
		lexer_parser_analyzer(shell);
		if (task_master(shell) != SUCCESS)
			quit_shell(shell, EXIT_FAILURE, FALSE);
		//print_hash_map_dev(&shell->hash);
		save_history(&shell->term);
		free_prompt(shell);
	}
}
