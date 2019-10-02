/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/10/02 02:55:42 by mpivet-p         ###   ########.fr       */
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
	char	*line;
	int8_t	status;

	line = NULL;
	status = 1;
	credit(shell);

	/* Loop for prompt with status of GNL */
	while (status)
	{
		/* Base output for prompt */
		init_prompt();

		/* GNL */
		if (!(status = ft_getnextline(STDIN_FILENO, &line)))
			break ;

		/*
		**	[NEED REWORK] A lot of stuff happening here :
		**	- tokens parser (for now)
		**	- Exp handling
		**	- Builtins ? (Maybe not accurate for now with futurs implementations)
		**	- etc ...
		*/

		if (get_tokens(shell, line) != SUCCESS) /* ft_strsplit with for now tab and space charset */
		{
			free_prompt(shell, line);
			continue ;
		}

		/* DEBUG */
		print_tokens(shell);

		/* Same here, mainly binary executions, need rework */
		if (exec_builtin(shell) == FAILURE)
			exec_process(shell, shell->env);
		free_prompt(shell, line);
	}
	ft_strdel(&line);
}
