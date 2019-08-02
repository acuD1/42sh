/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/08/02 16:06:00 by fcatusse         ###   ########.fr       */
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
	char		buff[READ_SIZE];
	t_read		term;

	line = NULL;
	status = 1;
	credit(shell);

	/* BETA */
	term.history = NULL;
	term.history_index = NULL;
	term.env = set_envp(shell);

	init_termcaps();
	init_config();
	/* Loop for prompt */
	while (status)
	{
		/* Base output for prompt */
		//init_prompt();
		display_prompt(&term);
		ft_bzero(term.buffer, term.width);
		while (read(0, buff, READ_SIZE))
		{
			if (check_caps(buff, &term) == TRUE)
				continue ;
			else
				break ;
		}
		free(term.prompt);
		/*
		**	[NEED REWORK] A lot of stuff happening here :
		**	- tokens parser (for now)
		**	- Exp handling
		**	- Builtins ? (Maybe not accurate for now with futurs implementations)
		**	- etc ...
		*/
		line = ft_strdup(term.buffer);
		if (get_tokens(shell, line) != SUCCESS) /* ft_strsplit with for now tab and space charset */
		{
			free_prompt(shell, line);
			continue ;
		}

		/* DEBUG */
		//print_tokens(shell);

		/* Same here, mainly binary executions, need rework */
		exec_process(shell, shell->env);
		save_history(&term);
		free_prompt(shell, line);
	}
	//ft_strdel(&line);
}
