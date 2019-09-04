/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_buffer.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:48:15 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/04 15:40:03 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

/*
** Delete last command insert in buffer and insert the new one
** Read again buff if another tab key is pressed => return TRUE
*/

uint8_t			read_again(char **prev_b, char *buf, char *name, t_read *input)
{
	delete_last_cmd(*prev_b, input);
	if (is_dir(name) == TRUE)
		ft_strcat(name, "/");
	insert_str_in_buffer(name, input);
	if (xread(0, buf, READ_SIZE) > 0)
	{
		if (buf[0] == '\t')
		{
			*prev_b = name;
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (FALSE);
}

/*
** To complete files if char inserted match with any files in current dir
*/

void			to_complete_buffer(char *buf, char *last_buf,
						char *to_find, t_read *input)
{
	struct dirent	*data;
	DIR		*dir;
	char		current_dir[BUFF_SIZE];
	int		found;

	if (!getcwd(current_dir, BUFF_SIZE))
		return ;
	dir = opendir(current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (isstart(data->d_name, to_find))
		{
			found = TRUE;
			if (read_again(&last_buf, buf, data->d_name, input) == TRUE)
				continue ;
			else
			{
				closedir(dir);
				return ;
			}
		}
	}
	found == TRUE ? to_complete_buffer(buf, last_buf, to_find, input) : 0;
}
