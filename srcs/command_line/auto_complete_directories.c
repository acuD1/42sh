/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_directories.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 15:17:29 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/01 16:03:45 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void				read_directories(char *buf, char *to_find, t_read *input)
{
	DIR				*dir;
	struct dirent	*data;
	char			*tmp;

	if (is_dir(to_find))
	{
		dir = opendir(to_find);
		while ((data = readdir(dir)) != NULL)
		{
			tmp = ft_strjoin(to_find, data->d_name);
			if (is_dir(tmp))
			{
				ft_strcat(data->d_name, "/");
				insert_str_in_buffer(data->d_name, input);
				input->found = TRUE;
			}
			else
				continue ;
			if (is_tab(buf, data->d_name, input) == TRUE)
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
	read_directories(buf, to_find, input);
}
