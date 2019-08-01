/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_current_dir.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:55:05 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/01 16:22:01 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Return only TRUE if tab key is pressed
*/

uint8_t				is_tab(char *buf, char *d_name, t_read *input)
{
	if (read(0, buf, READ_SIZE) > 0)
	{
		if (buf[0] == '\t')
		{
			delete_last_cmd(d_name, input);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (FALSE);
}

/*
** Display all files in current directory if no any char is inserted
** That display not hidden files in current directory while tab key is pressed
*/

void				display_current_directory(char *buf, t_read *input)
{
	struct dirent	*data;
	DIR				*dir;
	char			current_dir[BUFF_SIZE];

	if (!getcwd(current_dir, BUFF_SIZE))
		return ;
	dir = opendir(current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (data->d_name[0] != '.')
			insert_str_in_buffer(data->d_name, input);
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
	display_current_directory(buf, input);
}
