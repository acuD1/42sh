/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/19 16:47:18 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Ok so here we have our prompt. this is a basic one from minishell.
**	The current format is mainly for testing purpose.
**	free_prompt is our main fonction that free almost everythings
**	wiches are globals variables, such as tokens, env list etc...
*/

// static int	match_brackets(char a, char b)
// {
// 	return ((a == '[' && b == ']') || (a == '{' && b == '}') \
// 				|| (a == '(' && b == ')'));
// }

// static int	check_brackets(char *str)
// {
// 	int		i;
// 	int		top;
// 	int		stack[4096];

// 	i = 0;
// 	top = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '(' || str[i] == '{' || str[i] == '[')
// 			stack[++top] = str[i];
// 		if (str[i] == ')' || str[i] == '}' || str[i] == ']')
// 			if (!match_brackets(stack[top--], str[i]))
// 				return (0);
// 		i += 1;
// 	}
// 	return (!top);
// }

// static int	match_quotes(char a, char b)
// {
// 	return ((a == '\"' && b == '\"') || (a == '\'' && b == '\'') \
// 				|| (a == '`' && b == '`'));
// }

// static int	check_quote(char *str)
// {
// 	int		i;
// 	int		top;
// 	int		stack[4096];

// 	i = 0;
// 	top = 0;
// 	while (str[i])
// 	{
// 		if (str[i] == '\"' || str[i] == '\'' || str[i] == '`')
// 			stack[++top] = str[i];
// 		if (str[i] == '\"' || str[i] == '\'' || str[i] == '`')
// 			if (!match_quotes(stack[top--], str[i]))
// 				return (0);
// 		i += 1;
// 	}
// 	return (!top);
// }



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

	term.buffer = ft_memalloc(BUFF_SIZE);
	init_history(&term);
	/* Loop for prompt */
	while (status)
	{
		/* Base output for prompt */
		// line = ft_strdup(init_prompt(&term));

		/* GNL */
		init_prompt(&term);
		line = ft_strdup(term.buffer);
		/*
		**	[NEED REWORK] A lot of stuff happening here :
		**	- tokens parser (for now)
		**	- Exp handling
		**	- Builtins ? (Maybe not accurate for now with futurs implementations)
		**	- etc ...
		// */
		// if (check_brackets(line))
			lexer(shell, line);
		// else
			// error_quotes_brackets(line);
		// ast = parser(shell, parser);˚˚˚∫
		// exec_process(shell, shell->env);
		free_prompt(shell, line);
		// exec_process(shell, shell->env);

	}
	ft_strdel(&term.buffer);
}
