/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:47:06 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/27 00:02:21 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
 **	  Termcaps capabilities:
 **	  - `up' => to move the cursor vertically up one line
 **	  - `cr' => to move the cursor to the beginning of the line it is on
 **	  - `clr_lines' => to clear line from the cursor and following lines
 */

void		goto_prompt(t_read *line)
{
	while (line->y-- > 0)
		xtputs(line->tcaps[KEY_UP], 1, my_outc);
	xtputs(line->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(line->tcaps[CLR_LINES], 1, my_outc);
	free(line->prompt);
	display_prompt(line);
}

/*
 **	  Display prompt as the current directory
 **	  Store some datas for pressed keys
 */

t_read		*display_prompt(t_read *term)
{
	char	path[BUFF_SIZE + 1];

	ft_bzero(path, BUFF_SIZE + 1);
	if (!getcwd(path, BUFF_SIZE))
	{
		term->prompt = ft_strdup("<< 42sh >> ");
		term->prompt_len = ft_strlen(term->prompt);
	}
	else
	{
		term->prompt = ft_strdup(ft_strrchr(path, '/'));
		term->prompt_len = ft_strlen(term->prompt) + 7;
	}
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	ft_dprintf(STDOUT_FILENO, "%s%s<< %s >>%s ", C_BOLD, C_Y, term->prompt + 1, C_X);
	return (term);
}

void		get_y(t_read *input)
{
	char	buf[16];
	int	i;
	char	ch;
	char	*tmp;

	i = 0;
	ch = 0;
	ft_bzero(buf, 16);
	write(1, "\033[6n", 4);
	while (ch != 'R')
	{
		xread(0, &ch, 1);
		buf[i] = ch;
		i++;
	}
	tmp = ft_strsub(buf, 2, 2);
	input->y_li = atoi(tmp);
	ft_strdel(&tmp);
}

/*
 **	  Clear the last buffer/line inserted & Display current prompt
 **	  Launch line edition: read stdin until enter key is pressed
 **	  The current buffer is saved in a history list
 */

void		init_prompt(t_core *shell, t_read *term)
{
	char	buff[READ_SIZE + 1];

	shell->history = term->history;
	ft_bzero(buff, READ_SIZE + 1);
	ft_bzero(term->buffer, BUFF_SIZE);
	init_config(shell);
	init_termcaps(term);
	display_prompt(term);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		get_y(term);
		if (check_caps(buff, term) == TRUE)
		{
			ft_bzero(buff, READ_SIZE + 1);
			continue ;
		}
		else
			break ;
	}
	if (check_quotes(term) == FALSE)
	{
		remove_newline(term);
		check_expansions(term);
		save_history(term);
	}
	reset_config(shell, term);
	shell->buff = term->buffer;
}
