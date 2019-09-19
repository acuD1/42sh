/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/11 11:22:34 by fcatusse         ###   ########.fr       */
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

	// t_parser *parser;
	// t_ast	*ast;

	line = NULL;
	status = 1;
	credit(shell);

	/* BETA */
	term.history = NULL;
	term.history_index = NULL;
	term.env = set_envp(shell);
	term.new_line = 0;

	init_termcaps();
	init_history(&term);
	/* Loop for prompt */
	while (status)
	{
		/* Base output for prompt */
		line = ft_strdup(init_prompt(&term));

		/* GNL */
		/*
		**	[NEED REWORK] A lot of stuff happening here :
		**	- tokens parser (for now)
		**	- Exp handling
		**	- Builtins ? (Maybe not accurate for now with futurs implementations)
		**	- etc ...
		*/
		lexer(shell, line);
		// ast = parser(shell, parser);˚˚˚∫
		/* DEBUG */
		// print_tokens(shell);

		/* Same here, mainly binary executions, need rework */
		// exec_process(shell, shell->env);
		free_prompt(shell, line);
	}
	//ft_strdel(&line);
}
