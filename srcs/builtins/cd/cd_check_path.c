/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:14:23 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 14:30:48 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>
#include <unistd.h>

int8_t		cd_check_path(const char *path)
{
	int		errnum;

	errnum = 0;
	if (access(path, F_OK) == 0)
		errnum = is_a_dir(path);
	errnum = (errnum == EISDIR) ? 0 : errnum;
	if (errnum == 0)
		errnum = ft_access(path, X_OK);
	return (errnum);
}

int			check_cd_argument(t_process *process, int ac)
{
	if ((process->av[1][0] != '-' && ac > 2)
		|| (process->av[1][0] == '-' && ac > 3))
	{
		dprintf(STDERR_FILENO, "42sh: cd: too many arguments\n");
		return (FAILURE);
	}
	return (SUCCESS);
}
