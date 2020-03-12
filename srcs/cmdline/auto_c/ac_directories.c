/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_directories.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:27:09 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/12 15:06:44 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <dirent.h>
#include "sh42.h"

static u_int8_t	is_exe(const char *dir)
{
	struct stat	buff;

	if (lstat(dir, &buff) == FAILURE)
		return (FALSE);
	if (!is_dot(dir) && ((S_IXUSR & buff.st_mode) || (S_IXGRP & buff.st_mode)
			|| S_IXOTH & buff.st_mode))
		return (TRUE);
	else
		return (FALSE);
}

static int8_t	ac_dir(t_read *term, char *dir, const char *to_find)
{
	char	*tmp;

	tmp = ft_strjoin(to_find, dir);
	if ((is_dir(tmp) && !ft_isstart(dir, ".")) || is_exe(dir))
	{
		if (is_dir(tmp))
			ft_strcat(dir, "/");
		insert_str_in_buffer(dir, term);
		term->flag = TRUE;
		ft_strdel(&tmp);
	}
	else
	{
		ft_strdel(&tmp);
		return (SUCCESS);
	}
	if (is_tab(dir, term) == TRUE)
		return (SUCCESS);
	else
		return (FAILURE);
}

static void		auto_complete_directory(t_read *term, const char *to_find)
{
	struct dirent	*data;
	DIR				*dir;
	char			*tmp;

	dir = opendir("/");
	tmp = ft_strdup(to_find);
	while ((data = readdir(dir)) != NULL)
	{
		if (ft_strnequ(to_find + 1, data->d_name, ft_strlen(to_find)))
		{
			delete_last_cmd(tmp, term);
			ft_strdel(&tmp);
			tmp = ft_strjoin("/", data->d_name);
			tmp = ft_strjoinf(tmp, "/", 1);
			insert_str_in_buffer(tmp, term);
		}
	}
	ft_strdel(&tmp);
	closedir(dir);
}

void			read_directories(const char *to_find, t_read *term)
{
	struct dirent	*data;
	DIR				*dir;

	dir = NULL;
	if (to_find[ft_strlen(to_find) - 1] != '/')
		auto_complete_directory(term, to_find);
	else if (is_dir(to_find) && (dir = opendir(to_find)))
	{
		while ((data = readdir(dir)) != NULL)
		{
			if (ac_dir(term, data->d_name, to_find) == SUCCESS)
				continue ;
			else
			{
				term->flag = FALSE;
				break ;
			}
		}
		closedir(dir);
	}
	else
		term->flag = FALSE;
	if (term->flag == TRUE)
		read_directories(to_find, term);
}
