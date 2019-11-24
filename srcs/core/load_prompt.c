/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_prompt.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 11:58:29 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/24 14:27:39 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Ok so here we have our prompt. this is a basic one from minishell.
**	The current format is mainly for testing purpose.
**	free_prompt is our main fonction that free almost everythings
**	wiches are globals variables, such as tokens, env list etc...
*/

void			free_history(t_core *shell)
{
	t_lst *tmp;

	int i = 1;
	while (shell->history)
	{
		dprintf(STDERR_FILENO, "-%d- |%s|\n", i++, shell->history->content);
		free(shell->history->content);
		//free(shell->history);
		tmp = shell->history;
		shell->history = shell->history->next;
		free(tmp);
	//	shell->history = shell->history->next;
	}
	//free(shell->history);
}

void			load_prompt(t_core *shell)
{
	int8_t		status;
	t_read		term;

	status = 1;
	credit(shell);
	init_cmd_line(&term, shell);
	while (status)
	{
		init_prompt(shell, &term);
		lexer_parser_analyzer(shell, shell->buff);
		if (task_master(shell) != SUCCESS)
			exit(1);
		free_prompt(shell, shell->buff);
		//break;
		//exit(24);
	}
	//dprintf(STDERR_FILENO, "EXIT\n");
   //free_history(shell);
	//free(shell->history);
	ft_strdel(&shell->buff);
}
