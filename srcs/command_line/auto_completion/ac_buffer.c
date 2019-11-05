/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:30 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/05 20:24:53 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

/*
**		Delete last command insert in buffer and insert the new one
**		Read again buff if another tab key is pressed => return TRUE
*/

uint8_t			read_again(char **prev_b, char *path, char *name, t_read *input)
{
	uint64_t	value;
	char		buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	delete_last_cmd(*prev_b, input);
	if (is_dir(path) == TRUE)
		ft_strcat(name, "/");
	insert_str_in_buffer(name, input);
	if (xread(0, buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		if (value == TAB_KEY)
		{
			*prev_b = name;
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (FALSE);
}

uint8_t		get_dir(char *prev_b, char *to_find, char *current_dir)
{
	int	found;

	found = ft_strlen(to_find);
	while (to_find[--found])
	{
		if (to_find[found] == '/')
		{
			ft_bzero(current_dir, BUFF_SIZE);
			ft_strncpy(current_dir, prev_b, found + 1);
			to_find = ft_strrchr(to_find, '/') + 1;
			ft_bzero(prev_b, ft_strlen(prev_b));
			ft_strcpy(prev_b, to_find);
			return (TRUE);
		}
	}
	return (FALSE);
}

DIR			*update_curr_dir(char *to_find, char *prev_b, char *curr_dir)
{
	DIR             *dir;

	if (get_dir(prev_b, to_find, curr_dir))
		ft_strcpy(to_find, prev_b);
	else if (getcwd(curr_dir, BUFF_SIZE))
		ft_strcat(curr_dir, "/");
	else
		return (NULL);
	if ((dir = opendir(curr_dir)) == NULL)
		return (NULL);
	return (dir);
}

/*
**		Reading data name off the current directory opened
**		Return FAILURE(-1) to stop reading (an error occured or no tab key pressed)
*/

int8_t			read_dir(char **prev_b, char *to_find, t_read *input)
{
	char            current_dir[BUFF_SIZE];
	struct dirent   *data;
	uint8_t		found;
	DIR		*dir;
	char            *path;

	if ((dir = update_curr_dir(to_find, *prev_b, current_dir)) == NULL)
		return (FAILURE);
	while ((data = readdir(dir)) != NULL)
	{
		if (isstart(data->d_name, to_find))
		{
			found = TRUE;
			path = ft_strjoin(current_dir, data->d_name);
			if (read_again(prev_b, path, data->d_name, input) == TRUE)
				continue ;
			else
			{
				closedir(dir);
				free(path);
				return (FAILURE);
			}
		}
	}
	return (found);
}

/*
**		To complete files if char inserted match with any files in current dir
*/

void			to_complete_buffer(char *prev_b, char *to_find, t_read *input)
{
	int		found;

	found = FALSE;
	if (isstart(to_find, "$"))
	{
		parse_env(prev_b, to_find, input);
		return ;
	}
	if ((found = read_dir(&prev_b, to_find, input)) == FAILURE)
		return ;
	found == TRUE ? to_complete_buffer(prev_b, to_find, input) : 0;
}
