/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:48:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 12:16:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"

/*
** To complete files if char inserted match with any files in current dir
** ToDo: Open recursively directories | [NORME]
*/
void			to_complete_buffer(char *buf, char *last_buf, char *to_find, t_read *input)
{
	struct dirent	*data;
	DIR		*dir;
	char		current_dir[100];
	int		found;

	if (!getcwd(current_dir, 100))
		return ;
	dir = opendir(current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (isstart(data->d_name, to_find))
		{
			found = TRUE;
			delete_last_cmd(buf, last_buf, input);
			insert_str_in_buffer(data->d_name, input);
			if (read(0, buf, 5) > 0)
			{
				if (buf[0] == '\t')
				{
					free(last_buf);
					last_buf = ft_strdup(data->d_name);
					continue ;
				}
				else
				{
					closedir(dir);
					return ;
				}
			}
		}
	}
	found == TRUE ? to_complete_buffer(buf, last_buf, to_find, input) : 0;
}
