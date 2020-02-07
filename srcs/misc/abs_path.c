/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:02:32 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/07 02:10:15 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		dir_backward(char *path)
{
	int		i;

	i = ft_strlen(path) - 1;
	if (i <= 0)
		return ;
	path[i] = 0;
	while (i > 0 && path[i] != '/')
	{
		path[i] = 0;
		i--;
	}
}

static int8_t	dir_forward(char *path)
{
	int		i;

	i = (path[0] == '/') ? 1 : 0;
	while (path[i] && path[i] != '/')
		i++;
	i++;
	if (i > MAX_PATH)
		return (FAILURE);
	ft_strncpy(path, path + i, MAX_PATH);
	return (SUCCESS);
}

static int8_t	dir_write(char *rel, char *abs)
{
	int		i;
	int		j;

	j = ft_strlen(abs);
	i = (rel[0] == '/') ? 1 : 0;
	if (abs[j - 1] != '/')
		ft_strcat(abs + j++, "/");
	while (rel[i] && rel[i] != '/')
	{
		if (j > MAX_PATH)
			return (FAILURE);
		abs[j] = rel[i];
		j++;
		i++;
	}
	if (rel[i] != 0)
		abs[j++] = '/';
	abs[j] = 0;
	return (SUCCESS);
}

/*
**	Check if distance between two '/' is <= 255 and is canonical path <= 1024
*/

static int8_t	check_filename_length(char *str)
{
	int		filename;
	int		i;

	filename = 0;
	i = 1;
	while (str[i])
	{
		filename++;
		if (str[i] == '/')
			filename = 0;
		if (filename > 255)
			return (FAILURE);
		i++;
	}
	return (SUCCESS);
}

/*
**	Transform path in canonical path:
**	.././bar to /foo/bar etc.
*/

int8_t			get_canonical_path(char *path, char *abs)
{
	char	rel[MAX_PATH + 1];

	ft_bzero(abs, MAX_PATH + 1);
	ft_bzero(rel, MAX_PATH + 1);
	if (path[0] == '/')
		abs[0] = '/';
	else
		getcwd(abs, MAX_PATH);
	ft_strcpy(rel, path);
	while (rel[0] != 0)
	{
		if (rel[0] == '.' && rel[1] == '.' && (rel[2] == '/' || rel[2] == 0))
			dir_backward(abs);
		else if (!(rel[0] == '.' && (rel[1] == '/' || rel[1] == 0)))
			dir_write(rel, abs);
		if (dir_forward(rel) != SUCCESS)
			return (FAILURE);
	}
	return (check_filename_length(abs));
}
