/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_directories.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:27:09 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/10 19:17:39 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t			is_exe(char *dir)
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

uint8_t			ac_dir(t_read *input, char *buf, char *dir, char *to_find)
{
	char		*tmp;

	tmp = ft_strjoin(to_find, dir);
	if ((is_dir(tmp) && !isstart(dir, ".")) || is_exe(dir))
	{
		if (is_dir(tmp))
			ft_strcat(dir, "/");
		insert_str_in_buffer(dir, input);
		input->found = TRUE;
		free(tmp);
	}
	else
	{
		free(tmp);
		return (SUCCESS);
	}
	if (is_tab(buf, dir, input) == TRUE)
		return (SUCCESS);
	else
		return (FAILURE);
}

void			read_directories(char *buf, char *to_find, t_read *input)
{
	struct dirent	*data;
	DIR				*dir;

	if (is_dir(to_find) && (dir = opendir(to_find)))
	{
		while ((data = readdir(dir)) != NULL)
		{
			if (ac_dir(input, buf, data->d_name, to_find) == SUCCESS)
				continue ;
			else
			{
				closedir(dir);
				return ;
			}
		}
	}
	else
		return ;
	input->found == TRUE ? read_directories(buf, to_find, input) : 0;
}
