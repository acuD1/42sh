/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path_tools.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:55:13 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 21:10:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	dir_backward(char *path)
{
	size_t	i;

	i = ft_strlen(path);
	if (i <= 1)
		return ;
	i--;
	path[i] = 0;
	while (i > 0 && path[i] != '/')
	{
		path[i] = 0;
		i--;
	}
}

int8_t	dir_forward(char *path)
{
	size_t	i;

	i = (path[0] == '/') ? 1 : 0;
	while (path[i] && path[i] != '/')
		i++;
	i++;
	if (i > MAX_PATH)
		return (FAILURE);
	ft_strncpy(path, path + i, MAX_PATH);
	return (SUCCESS);
}

int8_t	dir_write(const char *rel, char *abs)
{
	size_t	i;
	size_t	j;

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

int8_t	check_filename_length(const char *str)
{
	size_t	filename;
	size_t	i;

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
