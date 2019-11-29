/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:10:29 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/29 05:05:12 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			init_cmd_line(t_read *term, t_core *shell)
{
	term->history = NULL;
	term->history_index = NULL;
	term->shell = shell;
	term->new_line = 0;
	term->found = 0;
	term->buffer = ft_memalloc(BUFF_SIZE);
	term->tmp_buff = NULL;
	if (get_size(term) != SUCCESS)
		quit_shell(shell, 1);
	init_history(term);
}

/*
**	Store current config in a globale var
**	Set new attributes to term config
**	- ICANON enable non-canonical mode
**	- ECHO disable echo input characters
*/

uint8_t				init_config(t_core *shell)
{
	if (tgetent(NULL, "xterm-256color") == FAILURE)
	{
		// Display error msg
		return (FAILURE);
	}
	if (tcgetattr(STDIN_FILENO, &(shell->old_t)) == FAILURE)
	{
		// Display error msg
		return (FAILURE);
	}
	shell->new_t = shell->old_t;
	shell->new_t.c_lflag &= ~(ICANON | ECHO);
	shell->new_t.c_cc[VMIN] = 1;
	shell->new_t.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &(shell->new_t)) == FAILURE)
	{
		// Display error msg
		return (FAILURE);
	}
	return (SUCCESS);
}

/*
**	Restore the old term config
**	Reset term when exit, before launch another shell, set term in bg..
*/

uint8_t			reset_config(t_core *shell, t_read *input)
{
	tcsetattr(STDOUT_FILENO, TCSANOW, &(shell->old_t));
	if (input->prompt) // secu
	{
		free(input->prompt);
		input->prompt = NULL;
	}
	ft_strdel(&input->tmp_buff); // pas besoin de secu, ft_strdel est secur
	return (SUCCESS);
}
