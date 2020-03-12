/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_directories.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:27:09 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/08 16:41:16 by arsciand         ###   ########.fr       */
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

void			read_directories(const char *to_find, t_read *term)
{
	struct dirent	*data;
	DIR				*dir;

	dir = NULL;
	if (is_dir(to_find) && (dir = opendir(to_find)))
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
	}
	else
		term->flag = FALSE;
	closedir(dir);
	if (term->flag == TRUE)
		read_directories(to_find, term);
}
