/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_complete_current_dir.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 13:55:05 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/24 16:42:02 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Return only TRUE if tab key is pressed
*/

uint8_t			is_tab(char *buf, char *d_name, t_read *input)
{
	ft_bzero(buf, READ_SIZE + 1);
	if (read(0, buf, READ_SIZE) > 0)
	{
		if (buf[0] == TAB_KEY)
		{
			delete_last_cmd(d_name, input);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (FALSE);
}

uint8_t			is_dot(char *d_name)
{
	if (!ft_strcmp(d_name, "."))
		return (TRUE);
	else if (!ft_strcmp(d_name, ".."))
		return (TRUE);
	return (FALSE);
}

/*
** Display all files in current directory if no any char is inserted
** That display not hidden files in current directory while tab key is pressed
*/

void			display_current_directory(char *buf, t_read *input, char *curr_dir)
{
	struct dirent	*data;
	DIR		*dir;
	char		current_dir[BUFF_SIZE];

	if (input->ac > 1 && is_dir(curr_dir))
		ft_strcpy(current_dir, curr_dir);
	else
		if (!getcwd(current_dir, BUFF_SIZE))
			return ;
	dir = opendir(current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (is_dot(data->d_name) == FALSE)
		{
			if (is_dir(data->d_name) == TRUE)
				ft_strcat(data->d_name, "/");
			insert_str_in_buffer(data->d_name, input);
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
	display_current_directory(buf, input, curr_dir);
}
