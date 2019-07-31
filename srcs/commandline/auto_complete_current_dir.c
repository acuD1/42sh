/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_current_dir.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:55:05 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 12:16:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"

/*
** Display all files in current directory if no any char is inserted
** ToDo: Open recursively directories
*/
void			display_current_directory(char *buf, t_read *input)
{
	struct dirent	*data;
	DIR		*dir;
	char		current_dir[BUFF_SIZE];

	if (!getcwd(current_dir, BUFF_SIZE))
		return ;
	dir = opendir(current_dir);
	while ((data = readdir(dir)))
	{
		insert_str_in_buffer(data->d_name, input);
		if (read(0, buf, 5) > 0)
		{
			if (buf[0] == '\t')
			{
				delete_last_cmd(buf, data->d_name, input);
				continue ;
			}
			else
			{
				closedir(dir);
				return ;
			}
		}
	}
	display_current_directory(buf, input);
}
