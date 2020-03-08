/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:02:32 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/03/08 15:41:45 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

/*
**	Transform path in canonical path:
**	.././bar to /foo/bar etc.
*/

static int8_t	path_resolver(char *rel, char *abs)
{
	while (rel[0] != 0)
	{
		if (rel[0] == '.' && rel[1] == '.' && (rel[2] == '/' || rel[2] == 0))
			dir_backward(abs);
		else if (!(rel[0] == '.' && (rel[1] == '/' || rel[1] == 0)))
			dir_write(rel, abs);
		if (dir_forward(rel) != SUCCESS)
			return (FAILURE);
	}
	return (SUCCESS);
}

int8_t			get_canonical_path
	(t_core *shell, const char *path, char *abs, char *pwd)
{
	char	rel[MAX_PATH + 1];

	ft_bzero(abs, MAX_PATH + 1);
	ft_bzero(rel, MAX_PATH + 1);
	if (path[0] == '/')
		abs[0] = '/';
	else
	{
		if (shell && shell->cd.pwd_error >= TRUE)
			ft_strcpy(abs, pwd);
		else
			getcwd(abs, MAX_PATH);
	}
	ft_strcpy(rel, path);
	if (path_resolver(rel, abs) != SUCCESS)
		return (FAILURE);
	if (check_filename_length(abs) == FAILURE)
		return (FAILURE);
	if (shell && shell->cd.pwd_error >= TRUE)
	{
		ft_bzero(pwd, MAX_PATH + 1);
		ft_strcpy(pwd, abs);
	}
	return (SUCCESS);
}
