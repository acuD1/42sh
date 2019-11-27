/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   term_config.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:10:29 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/26 17:21:44 by fcatusse         ###   ########.fr       */
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
	term->sub_prompt = 0;
	term->buffer = NULL;
	term->tmp_buff = NULL;
	init_history(term);
}

/*
**	Store current config in a globale var
**	Set new attributes to term config
**	- ICANON enable non-canonical mode
**	- ECHO disable echo input characters
*/

uint8_t				init_config(void)
{
	struct termios		new_t;

	if (tgetent(NULL, "xterm-256color") == FAILURE)
	{
		// Display error msg
		return (FAILURE);
	}
	if (tcgetattr(STDIN_FILENO, &old_t) == FAILURE)
	{
		// Display error msg
		return (FAILURE);
	}
	new_t = old_t;
	new_t.c_lflag &= ~(ICANON | ECHO);
	new_t.c_cc[VMIN] = 1;
	new_t.c_cc[VTIME] = 0;
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_t) == FAILURE)
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

uint8_t			reset_config(t_read *input)
{
	if (tcsetattr(STDOUT_FILENO, TCSANOW, &old_t) == FAILURE)
	{
		// Display error msg
		return (FAILURE);
	}
	old_t.c_lflag |= (ICANON | ECHO);
	ft_strdel(&input->prompt);
	(input->tmp_buff) ? ft_strdel(&input->tmp_buff) : 0;
	return (SUCCESS);
}
