/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:47:06 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/04 12:29:44 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Termcaps capabilities:
**	- `cr' => to move the cursor to the beginning of the line it is on
**	- `ce' => to clear from the cursor to the end of the current line
**	- `up' => to move the cursor vertically up one line
*/

void		goto_prompt(t_read *line)
{
	/* if (line->sub_prompt != FALSE) */
	/* { */
	/* 	goto_subprompt(line); */
	/* 	return ; */
	/* } */
	while (line->y-- > 0)
	{
		xtputs(xtgetstr("cr", NULL), 1, my_outc);
		xtputs(xtgetstr("ce", NULL), 1, my_outc);
		xtputs(xtgetstr("up", NULL), 1, my_outc);
	}
	xtputs(xtgetstr("cr", NULL), 1, my_outc);
	xtputs(xtgetstr("ce", NULL), 1, my_outc);
	free(line->prompt);
	display_prompt(line);
}

/*
**	Display prompt as the current directory
**	Store some datas for pressed keys
*/

t_read		*display_prompt(t_read *term)
{
	char	path[BUFF_SIZE + 1];

	ft_bzero(path, BUFF_SIZE + 1);
	if (!getcwd(path, BUFF_SIZE))
		term->prompt = ft_strdup("undefined");
	else
		term->prompt = ft_strdup(ft_strrchr(path, '/'));
	term->prompt_len = ft_strlen(term->prompt) + 7;
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term = get_size(term);
	dprintf(STDOUT_FILENO, "%s%s<< %s >>%s ", C_BOLD, C_Y, term->prompt + 1, C_X);
	return (term);
}

/*
**	Clear the last buffer/line inserted & Display current prompt
**	Launch line edition: read stdin until enter key is pressed
**	The current buffer is saved in a list history
*/

char		*init_prompt(t_read *term)
{
	char	buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE + 1);
	ft_bzero(term->buffer, BUFF_SIZE);
	init_config();
	display_prompt(term);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (check_caps(buff, term) == TRUE)
		{
			ft_bzero(buff, READ_SIZE);
			continue ;
		}
		else
			break ;
	}
	if (check_quotes(term) == FALSE)
	{
		remove_newline(term);
		save_history(term);
	}
	reset_config(term);
	return (term->buffer);
}
