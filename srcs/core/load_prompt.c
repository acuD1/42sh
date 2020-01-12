/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/12 21:33:42 by mpivet-p         ###   ########.fr       */
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

void			free_history(t_read *term)
{
	t_lst *tmp;

	int i = 1;
	while (term->history)
	{
		dprintf(STDERR_FILENO, "-%d- |%s|\n", i++, term->history->content);
		free(term->history->content);
		//free(term->history);
		tmp = term->history;
		term->history = term->history->next;
		free(tmp);
	//	term->history = term->history->next;
	}
	//free(term->history);
}

void			load_prompt(t_core *shell)
{
	int8_t		status;
	t_read		*term;

	status = 1;
	term = &(shell->cmd_line);
	credit(shell);
	init_cmd_line(term, shell);
	while (status)
	{
		/* Base output for prompt */
		init_prompt(shell, term);
		lexer_parser_analyzer(shell, term->buffer);
		if (task_master(shell) != SUCCESS)
			break ;
		save_history(term);
		free_prompt(shell, term->buffer);
	}
	free_history(term);
	ft_strdel(&(term->buffer));
}
