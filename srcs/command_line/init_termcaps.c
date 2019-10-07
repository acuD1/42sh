/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/07 18:45:26 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/ioctl.h>

/*
** Store the number of line and column in struct
*/

t_read			*get_size(t_read *data)
{
	struct winsize	size;

	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) == FAILURE)
		ft_putstr("ioctl error"); //call an error fct
	data->ws_col = size.ws_col;
	data->ws_li = size.ws_row;
	return (data);
}

void			stock_termcaps(t_termcaps *termcaps)
{
	termcaps->del = xtgetstr("dc", NULL);
	termcaps->save_cr = xtgetstr("sc", NULL);
	termcaps->reset_cr = xtgetstr("rc", NULL);
	termcaps->down = xtgetstr("do", NULL);
	termcaps->up = xtgetstr("up", NULL);
	termcaps->right = xtgetstr("nd", NULL);
	termcaps->left = xtgetstr("le", NULL);
	termcaps->cr = xtgetstr("cr", NULL);
	termcaps->ho = xtgetstr("ho", NULL);
	termcaps->clear = xtgetstr("cl", NULL);
	termcaps->clr_lines = xtgetstr("cd", NULL);
	termcaps->clr_end = xtgetstr("ce", NULL);
}

void			init_termcaps(t_read *term)
{
	char		*sh;
	char		bp[1024];

	term->termcaps = ft_memalloc(sizeof(t_termcaps));
	stock_termcaps(term->termcaps);
	if (!(sh = getenv("TERM")))
	{
		// Display error msg
		EXIT_FAILURE ;
	}
	if (tgetent(bp, sh) == FAILURE)
	{
		// Display error msg
		EXIT_FAILURE ;
	}
}
