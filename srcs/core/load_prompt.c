/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/10/26 15:49:48 by arsciand         ###   ########.fr       */
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
	int8_t		status;
	t_read		term;
	t_lst *tmp;

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
		// */
		// if (check_brackets(line))
		shell->lexer = lexer(shell->buff);
		shell->job_list = analyzer(shell);
		if (shell->job_list)
		{
			tmp = shell->job_list;
			while (tmp)
			{
				ft_printjob(((t_job*)tmp->content));
				tmp = tmp->next;
			}
		}

		/* DEBUG */
		//print_tokens(shell);

		/* Same here, mainly binary executions, need rework */
		//free_prompt(shell, term.buffer);
		//if (exec_builtin(shell) == FAILURE)
		//	exec_process(shell, shell->env);

		save_history(&term);
		free_prompt(shell, shell->buff);
	}
	ft_strdel(&term.buffer);
}
