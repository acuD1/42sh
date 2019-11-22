/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 12:47:06 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/22 21:18:11 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
 **	  Termcaps capabilities:
 **	  - `up' => to move the cursor vertically up one input
 **	  - `cr' => to move the cursor to the beginning of the input it is on
 **	  - `clr_inputs' => to clear input from the cursor and following inputs
 */

void		goto_prompt(t_read *input)
{
	while (input->y-- > 0)
		xtputs(input->tcaps[KEY_UP], 1, my_outc);
	xtputs(input->tcaps[LEFT_MARGIN], 1, my_outc);
	xtputs(input->tcaps[CLR_LINES], 1, my_outc);
	if (input->sub_prompt > 0)
		display_subprompt(input, input->prompt);
	else
		display_prompt(input);
}

/* void		get_y(t_read *input) */
/* { */
/* 	char	buf[16]; */
/* 	int	i; */
/* 	char	ch; */
/* 	char	*tmp; */
/*  */
/* 	i = 0; */
/* 	ch = 0; */
/* 	ft_bzero(buf, 16); */
/* 	write(1, "\033[6n", 4); */
/* 	while (ch != 'R') */
/* 	{ */
/* 		xread(0, &ch, 1); */
/* 		buf[i] = ch; */
/* 		i++; */
/* 	} */
/* 	tmp = ft_strsub(buf, 2, 2); */
/* 	input->y_li = ft_atoi(tmp) - 1; */
/* 	ft_strdel(&tmp); */
/* } */

/*
 **	  Display prompt as the current directory
 **	  Store some datas for pressed keys
 */

void		display_prompt(t_read *term)
{
	char	path[BUFF_SIZE + 1];

	ft_bzero(path, BUFF_SIZE + 1);
	if (!getcwd(path, BUFF_SIZE))
	{
		term->prompt = ft_strdup(PS1);
		term->prompt_len = ft_strlen(term->prompt);
	}
	else
	{
		term->prompt = ft_strdup(ft_strrchr(path, '/') + 1);
		term->prompt_len = ft_strlen(term->prompt) + 2;
	}
	term->x = term->prompt_len;
	term->x_index = term->x;
	term->y = 0;
	term->width = term->x;
	term->sub_prompt = 0;
	ft_dprintf(STDOUT_FILENO, "%s%s%s$ %s", C_BOLD, C_Y, term->prompt, C_X);
	xtputs(term->tcaps[CLR_LINES], 1, my_outc);
}

/*
**	  Clear the last buffer/input inserted & Display current prompt
**	  Launch input edition: read stdin until enter key is pressed
**	  The current buffer is saved in a history list
*/

void		init_prompt(t_read *term)
{
	char	buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	term->buffer = ft_memalloc(BUFF_SIZE);
	init_config();
	init_termcaps(term);
	display_prompt(term);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (check_caps(buff, term) == TRUE)
			ft_bzero(buff, READ_SIZE);
		else
			break ;
	}
	if (check_quotes(term) == FALSE)
	{
		//remove_newline(term);
		check_expansions(term);
	}
	ft_strdel(&term->prompt);
	reset_config(term);
}
