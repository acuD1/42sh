/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_directories.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:27:09 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/02 13:18:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t				ac_directories(t_read *input, char *buf, char *dir, char *to_find)
{
	char			*tmp;

	tmp = ft_strjoin(to_find, dir);
	if (is_dir(tmp) && !isstart(dir, "."))
	{
		ft_strcat(dir, "/");
		insert_str_in_buffer(dir, input);
		input->found = TRUE;
	}
	else
		return (SUCCESS);
	if (is_tab(buf, dir, input) == TRUE)
		return (SUCCESS);
	else
		return (FAILURE);
}

void				read_directories(char *buf, char *to_find, t_read *input)
{
	DIR				*dir;
	struct dirent	*data;

	if (is_dir(to_find) && (dir = opendir(to_find)))
	{
			while ((data = readdir(dir)) != NULL)
			{
				if (ac_directories(input, buf, data->d_name, to_find) == SUCCESS)
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
