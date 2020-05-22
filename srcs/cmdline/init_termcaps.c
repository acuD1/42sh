/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/23 16:54:32 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/ioctl.h>
#include <termcap.h>
#include <unistd.h>
#include <stdlib.h>

/*
**	Store datas of terminal's line/column
*/

int8_t			get_size(t_read *term)
{
	struct winsize	size;

	ft_bzero(&size, sizeof(struct winsize));
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) != SUCCESS)
	{
		if ((term->ws_col = tgetnum("co")) < 0
			|| (term->ws_li = tgetnum("li")) < 0)
		{
			ft_dprintf(STDERR_FILENO, "42sh: ioctl error\n");
			quit_shell(get_core(NULL), EXIT_FAILURE, FALSE);
		}
		return (SUCCESS);
	}
	term->ws_col = size.ws_col;
	term->ws_li = size.ws_row;
	return (SUCCESS);
}

/*
**	Stock termcaps capabilities in a static array
*/

static int8_t	stock_termcaps(t_read *term)
{
	static char	*termcaps[CAPS_NBR] = {"sc", "rc", "do", "up", "nd"
		, "le", "cr", "ho", "cl", "cd", "ce", "so", "se", "bl"};
	size_t		i;

	i = 0;
	while (i < CAPS_NBR)
	{
		if ((term->tcaps[i] = tgetstr(termcaps[i], NULL)) == NULL)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/*
**	Initialization of terminal's termcaps capabilities
*/

int8_t			init_termcaps(t_read *term)
{
	char	*sh;

	sh = getenv("TERM");
	if (tgetent(NULL, ((sh) ? sh : "xterm-256color")) == 0)
	{
		ft_dprintf(STDERR_FILENO, "42sh: tgetent error\n");
		return (FAILURE);
	}
	if (stock_termcaps(term) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, "42sh: termcaps error\n");
		return (FAILURE);
	}
	if (get_size(term) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}
