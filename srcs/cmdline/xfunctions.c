/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfunctions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:13:33 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/06 22:32:59 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <term.h>
#include "sh42.h"

/*
**	Some functions safe/protected
*/

void	xtputs(char *str, int i, int (*f)(int))
{
	t_core	*shell;

	shell = get_core(NULL);
	tputs(str, i, f);
}

char	*xtgetstr(char *id, char **area)
{
	char	*str;
	t_core	*shell;

	shell = get_core(NULL);
	if ((str = tgetstr(id, area)) == NULL)
	{
		dprintf(STDERR_FILENO, "42sh: tgetstr errror\n");
		quit_shell(shell, EXIT_FAILURE, TRUE);
	}
	return (str);
}

size_t	xread(int fd, char *buff, int size)
{
	int		ret;
	t_core	*shell;

	shell = get_core(NULL);
	if ((ret = read(fd, buff, size)) < 1)
	{
		if (ret == FAILURE)
		{
			dprintf(STDERR_FILENO, "42sh: read errror\n");
			quit_shell(shell, EXIT_FAILURE, TRUE);
		}
	}
	return (ret);
}
