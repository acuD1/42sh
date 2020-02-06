/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tmp_debug.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 17:13:59 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/06 18:35:23 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "sh42.h"

int8_t	debug_ailleurs(const char *path, const char *str)
{
	int8_t	fd;

	if ((fd = open(path, O_WRONLY)) < 0)
		return (FAILURE);
	dprintf(fd, "{%s}\n", str);
	return (SUCCESS);
}

int8_t	nono(const char *path)
{
	int8_t	fd;

	if ((fd = open(path, O_WRONLY)) < 0)
		return (FAILURE);
	return (fd);
}

void	ft_printtab(char **cmd)
{
	int		i;
	int8_t	j;

	i = 0;
	j = 0;
	if (cmd)
	{
		j = ft_tablen(cmd);
		dprintf(nono("/dev/ttys002"), "cmd {");
		while (cmd[i])
		{
			dprintf(nono("/dev/ttys002"), "'%s'", cmd[i]);
			i++;
		}
		dprintf(nono("/dev/ttys002"), "}\n");
	}
}
