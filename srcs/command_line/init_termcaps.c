/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_termcaps.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:35:58 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/09 15:01:00 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/ioctl.h>

/*
**	Store datas of terminal's line/column
*/

t_read   	         *get_size(t_read *data)
{
	struct winsize    size;

	ft_bzero(&size, sizeof(struct winsize));
	if (ioctl(STDIN_FILENO, TIOCGWINSZ, &size) != SUCCESS)
	{
		ft_dprintf(STDERR_FILENO, "IOCTL ERROR\n");
		if ((data->ws_col = tgetnum("co")) < 0 || (data->ws_li = tgetnum("li")) < 0)
		{
			ft_dprintf(STDERR_FILENO, "IOCTL AND TGETNUM FAILURE");
			return (NULL)
		}
		return (data);
	}
	data->ws_col = size.ws_col;
	data->ws_li = size.ws_row;
	return (data);
}

/*
**	Stock termcaps capabilities in a static array
*/

int8_t			stock_termcaps(t_read *term)
{
	static char	*termcaps[CAPS_NBR];
	int		i;

	i = -1;
	termcaps[0] = "dc";
	termcaps[1] = "sc";
	termcaps[2] = "rc";
	termcaps[3] = "do";
	termcaps[4] = "up";
	termcaps[5] = "nd";
	termcaps[6] = "le";
	termcaps[7] = "cr";
	termcaps[8] = "ho";
	termcaps[9] = "cl";
	termcaps[10] = "cd";
	termcaps[11] = "ce";
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
}
