/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/10 21:46:22 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Store datas of terminal's line/column
*/

int8_t			get_size(t_read *data)
{
	struct winsize    size;

	ft_bzero(&size, sizeof(struct winsize));
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) != SUCCESS)
	{
		if ((data->ws_col = tgetnum("co")) < 0 || (data->ws_li = tgetnum("li")) < 0)
		{
			ft_dprintf(STDERR_FILENO, "42sh: ioctl and tgetnum error");
			return (FAILURE);
		}
		return (SUCCESS);
	}
	data->ws_col = size.ws_col;
	data->ws_li = size.ws_row;
	return (SUCCESS);
}

/*
**	Stock termcaps capabilities in a static array
*/

int8_t			stock_termcaps(t_read *term)
{
	static char	*termcaps[CAPS_NBR] = {"dc", "sc", "rc", "do", "up", "nd"
		, "le", "cr", "ho", "cl", "cd", "ce"};
	int		i;

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

void			init_termcaps(t_read *term)
{
	char		*sh;
	char		bp[1024];

	if (stock_termcaps(term) == FAILURE)
		EXIT_FAILURE ; // Display error msg
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
	if (get_size(term) != SUCCESS)
	{
		//SHELL MUST LEAVE : Print message + exit
		quit_shell(get_core(NULL), 1, 0);
	}
}
