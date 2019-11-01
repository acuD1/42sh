/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   abs_path.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 14:02:32 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/15 00:29:35 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	dir_backward(char *path)
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

static void	dir_forward(char *path)
{
	int		i;

	i = (path[0] == '/') ? 1 : 0;
	while (path[i] && path[i] != '/')
	{
		i++;
	}
	i++;
	if (i >= MAX_PATH)
		return ;
	ft_strncpy(path, path + i, MAX_PATH);
}

static void	dir_write(char *rel, char *abs)
{
	int i;
	int j;

	j = ft_strlen(abs);
	i = (rel[0] == '/') ? 1 : 0;
	if (abs[j - 1] != '/')
		ft_strcat(abs + j++, "/");
	while (rel[i] && rel[i] != '/')
	{
		abs[j] = rel[i];
		j++;
		i++;
	}
	if (rel[i] != 0)
		abs[j++] = '/';
	abs[j] = 0;
}

char	*get_abs_path(char *path)
{
	char	abs[MAX_PATH + 1];
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
		dir_forward(rel);
	}
	return (ft_strdup(abs));
}
