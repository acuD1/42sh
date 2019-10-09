/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/10/07 16:45:09 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Ok so here we have our prompt. this is a basic one from minishell.
**	The current format is mainly for testing purpose.
**	free_prompt is our main fonction that free almost everythings
**	wiches are globals variables, such as tokens, env list etc...
*/

/*
**	TO DO:
*/

void			load_prompt(t_core *shell)
{
	char		*line;
	int8_t		status;
	t_read		term;

	line = NULL;
	status = 1;
	credit(shell);
	(void)line;
	/* BETA */
	term.history = NULL;
	term.history_index = NULL;

	term.shell = shell;
	term.new_line = 0;
	term.buffer = ft_memalloc(BUFF_SIZE);
	init_history(&term);
	/* Loop for prompt */
	while (status)
	{
		/* Base output for prompt */
		init_prompt(&term);
		line = ft_strdup(term.buffer);
		/*
		**	[NEED REWORK] A lot of stuff happening here :
		**	- tokens parser (for now)
		**	- Exp handling
		**	- Builtins ? (Maybe not accurate for now with futurs implementations)
		**	- etc ...
		*/

		if (get_tokens(shell, term.buffer) != SUCCESS) /* ft_strsplit with for now tab and space charset */
		{
	//		free_prompt(shell, term.buffer);
			continue ;
		}

		/* DEBUG */
		//print_tokens(shell);

		/* Same here, mainly binary executions, need rework */
		exec_process(shell, shell->env);
//		free_prompt(shell, term.buffer);
	}
	ft_strdel(&term.buffer);
}
