/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/12 10:06:36 by arsciand         ###   ########.fr       */
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

void			free_history(t_core *shell)
{	t_lst *tmp;

	while (shell->history)
	{
		free(shell->history->content);
		tmp = shell->history;
		shell->history = shell->history->next;
		free(tmp);
		free(shell->history);
	}
}

void			load_prompt(t_core *shell)
{
	int8_t		status;
	t_read		term;

	status = 1;
	credit(shell);
	/* BETA */
	init_cmd_line(&term, shell);
	/* Loop for prompt */
	while (status)
	{
		/* Base output for prompt */
		shell->history = term.history;
		init_prompt(&term);
		shell->buff = term.buffer;

		/*
		**	[NEED REWORK] A lot of stuff happening here :
		**	- tokens parser (for now)
		**	- Exp handling
		**	- Builtins ? (Maybe not accurate for now with futurs implementations)
		**	- etc ...
		*/

		dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "BUFF           [%s]\n", shell->buff);
		lexer_parser_analyzer(shell, term.buffer);
		debug_ailleurs("/dev/ttys002", "CE N'EST PLUS MA PARTIE");
		if (task_master(shell) != SUCCESS)
			exit(1);
		free_prompt(shell, shell->buff);
		save_history(&term);
		// ft_freejoblist(&shell->job_list);
	}
	//free_history(shell);
	ft_strdel(&shell->buff);
}
