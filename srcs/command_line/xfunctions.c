/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfunctions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:13:33 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/19 13:42:02 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <curses.h>

/*
**	Some functions safe/protected
*/

void		xtputs(char *str, int i, int (*f)(int))
{
		if (tputs(str, i, f) == ERR)
		{
			//Error fct
			dprintf(2, "tputs error.");
			exit(0);
		}
}

char		*xtgetstr(char *id, char **area)
{
	char	*str;

	if ((str = tgetstr(id, area)) == NULL)
	{
		//Error fct
		dprintf(2, "tgetstr error.");
		exit(0);
	}
	return (str);
}

size_t		xread(int fd, char *buff, int size)
{
	int	ret;

	if ((ret = read(fd, buff, size)) < 1)
	{
		if (ret == FAILURE)
		{
			//Error fct
			dprintf(2, "read error");
			exit(EXIT_FAILURE);
		}
	}
	return (ret);
}
