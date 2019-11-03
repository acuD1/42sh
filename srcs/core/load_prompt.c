/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/03 15:11:00 by arsciand         ###   ########.fr       */
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
	int8_t		status;
	t_read		term;
	//t_lst *tmp;

	// t_parser *parser;
	// t_ast	*ast;

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
		shell->buff = ft_strdup(term.buffer);
		/*
		**	[NEED REWORK] A lot of stuff happening here :
		**	- tokens parser (for now)
		**	- Exp handling
		**	- Builtins ? (Maybe not accurate for now with futurs implementations)
		**	- etc ...
		*/
		// if (get_tokens(shell, line) != SUCCESS) //// ft_strsplit with for now tab and space charset
		// {
		// 	free_prompt(shell, line);
		// 	continue ;
		// }
		lexer_parser_analyzer(shell, shell->buff);
		// ast = parser(shell, parser);˚˚˚∫
		/* DEBUG */
		// print_tokens(shell);

		lexer_parser_analyzer(shell, shell->buff);
		//debug_analyzer(shell);
		free_prompt(shell, shell->buff);
	}
	ft_strdel(&term.buffer);
}
