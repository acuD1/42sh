/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   xfunctions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/03 12:13:33 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/03 13:32:23 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <curses.h>

/*
**	Some functions safe/protected
*/

void	xtputs(char *str, int i, int (*f)(int))
{
	t_core	*shell;

	shell = get_core(NULL);
	if (tputs(str, i, f) == ERR)
	{
		ft_perror("tputs", NULL, 0);
		quit_shell(shell, EXIT_FAILURE, TRUE);
	}
}

char	*xtgetstr(char *id, char **area)
{
	char	*str;
	t_core	*shell;

	shell = get_core(NULL);
	if ((str = tgetstr(id, area)) == NULL)
	{
		ft_perror("tgetstr", NULL, 0);
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
			ft_perror("read", NULL, 0);
			quit_shell(shell, EXIT_FAILURE, TRUE);
		}
	}
	return (ret);
}

// Pareil a check les exit ici
