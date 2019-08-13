/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:36:42 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/13 01:01:33 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int		my_outc(int c)
{
	write(0, &c, 1);
	return (SUCCESS);
}

/*
**	Go up with termcap while there is newline
**	Go to first column to clear the line
*/

uint8_t		is_multiline(t_read *line)
{
	int	buff_index;

	if (ft_strchr(line->buffer, '\n'))
	{
		buff_index = line->x_index - line->prompt_len;
		while (line->y--)
		{
			while (line->buffer[buff_index] != '\n')
			{
				move_left(line->buffer, line);
				line->width--;
				buff_index--;
			}
			line->width--;
			buff_index--;
			tputs(tgetstr("ce", NULL), 1, my_outc);
			tputs(tgetstr("up", NULL), 1, my_outc);
		}
		tputs(tgetstr("cr", NULL), 1, my_outc);
		tputs(tgetstr("ce", NULL), 1, my_outc);
		display_prompt(line);
		return (TRUE);
	}
	return (FALSE);
}

/*
**	Move the cursor right to prompt and clear the line
**	If there are multilines => Go up to prompt and clear all lines
*/

void		goto_prompt(t_read *line)
{
	if (is_multiline(line) == TRUE)
		return ;
	while (line->x_index > line->prompt_len)
	{
		line->width--;
		move_left(line->buffer, line);
		if (line->y > 0 && line->x == 0)
			tputs(tgetstr("ce", NULL), 1, my_outc);
	}
	tputs(tgetstr("ce", NULL), 1, my_outc);
}

/*
**	Display prompt as the current directory
**	Store some datas for pressed keys
*/

t_read		*display_prompt(t_read *term)
{
	char	path[BUFF_SIZE + 1];

	if (!getcwd(path, BUFF_SIZE))
		term->prompt = ft_strdup("undefined");
	else
		term->prompt = ft_strdup(ft_strrchr(path, '/'));
	term->prompt_len = ft_strlen(term->prompt) + 6;
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term = get_size(term);
	term->new_line = FALSE;
	dprintf(STDOUT_FILENO, "%s%s<< %s >>%s ", C_BOLD, C_M, term->prompt + 1, C_X);
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

	init_config();
	ft_bzero(term->buffer, term->width);
	display_prompt(term);
	while (read(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (check_caps(buff, term) == TRUE)
		{
			ft_bzero(buff, READ_SIZE);
			continue ;
		}
		else
			break ;
	}
	free(term->prompt);
	if (check_quotes(term) == FALSE)
		save_history(term);
	reset_config();
	return (term->buffer);
}
