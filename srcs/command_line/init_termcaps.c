/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/03 17:20:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Store datas of terminal's line/column
*/

int8_t			get_size(t_read *term)
{
	struct winsize	size;

	ft_bzero(&size, sizeof(struct winsize));
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) != SUCCESS)
	{
		// Double assignation
		if ((term->ws_col = tgetnum("co")) < 0 || (term->ws_li = tgetnum("li")) < 0)
		{
			ft_perror("Ioctl and Tgetnum error", NULL, 0);
			quit_shell(get_core(NULL), EXIT_FAILURE, FALSE);
			return (FAILURE);
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
	static char	*termcaps[CAPS_NBR] = {"dc", "sc", "rc", "do", "up", "nd"
		, "le", "cr", "ho", "cl", "cd", "ce"};
	int			i;

	i = -1;
	while (++i < CAPS_NBR)
	{
		if (!(term->tcaps[i] = xtgetstr(termcaps[i], NULL)))
			return (FAILURE);
	}
	return (SUCCESS);
}

/*
**	Initialization of terminal's termcaps capabilities
*/

// Need rework here this is UGLY
void			init_termcaps(t_read *term)
{
	char	*sh;
	char	bp[1024];

	if (stock_termcaps(term) == FAILURE)
	{
		ft_perror("Get termcaps failed", NULL, 0);
		quit_shell(get_core(NULL), EXIT_FAILURE, FALSE);
	}
	if (!(sh = getenv("TERM")))
	{
		ft_perror("Getenv error", NULL, 0);
		quit_shell(get_core(NULL), EXIT_FAILURE, FALSE);
	}
	if (tgetent(bp, sh) == FAILURE)
	{
		ft_perror("Tgetent error", NULL, 0);
		quit_shell(get_core(NULL), EXIT_FAILURE, FALSE);
	}
	if (get_size(term) != SUCCESS)
	{
		ft_perror("Get term size failed", NULL, 0);
		quit_shell(get_core(NULL), EXIT_FAILURE, FALSE);
	}
}
