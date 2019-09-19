/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/19 13:35:14 by fcatusse         ###   ########.fr       */
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
	termcaps->del = ft_strdup(xtgetstr("dc", NULL));
	termcaps->save_cr = ft_strdup(xtgetstr("sc", NULL));
	termcaps->reset_cr = ft_strdup(xtgetstr("rc", NULL));
	termcaps->clr_end = ft_strdup(xtgetstr("ce", NULL));
	termcaps->down = ft_strdup(xtgetstr("do", NULL));
	termcaps->up = ft_strdup(xtgetstr("up", NULL));
	termcaps->right = ft_strdup(xtgetstr("nd", NULL));
	termcaps->left = ft_strdup(xtgetstr("le", NULL));
	termcaps->cr = ft_strdup(xtgetstr("cr", NULL));
	termcaps->clear = ft_strdup(xtgetstr("cl", NULL));
	termcaps->ho = ft_strdup(xtgetstr("ho", NULL));
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
