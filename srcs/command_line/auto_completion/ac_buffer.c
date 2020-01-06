/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:30 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/06 14:02:51 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t debugi(const char *path, char *str1, char *str2, int i)
{
    int fd;

	    if ((fd = open(path, O_WRONLY)) < 0)
		        return (FAILURE);
		dprintf(fd, "[%s] [%s] [%d]\n", str1, str2, i);
	   return (SUCCESS);
}

/*
**		Delete last command insert in buffer and insert the new one
**		Read again buff if another tab key is pressed => return TRUE
*/

uint8_t			read_again(char **prev_b, char *path, char *name, t_read *term)
{
	uint64_t	value;
	char		buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	delete_last_cmd(*prev_b, term);
	if (is_dir(path) == TRUE)
		ft_strcat(name, "/");
	insert_str_in_buffer(name, term);
	if (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		if (value == TAB_KEY)
		{
			ft_strdel(&*prev_b);
			*prev_b = ft_strdup(name);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (FALSE);
}

uint8_t			get_dir(char *prev_b, char *to_find, char *current_dir)
{
	int			found;
	char		*tmp;

	tmp = NULL;
	found = ft_strlen(to_find) - 1;
	while (found--)
	{
		if (to_find[found] == '/')
		{
			ft_bzero(current_dir, BUFF_SIZE);
			ft_strncpy(current_dir, prev_b, found + 1);
			tmp = ft_strdup(to_find);
			ft_strdel(&to_find);
			to_find = ft_strdup(ft_strrchr(tmp, '/') + 1);
			ft_strdel(&tmp);
			ft_strdel(&prev_b);
			prev_b = ft_strdup(to_find);
			return (TRUE);
		}
	}
	return (FALSE);
}

DIR				*update_curr_dir(char *to_find, char *prev_b, char *curr_dir)
{
	DIR			*dir;

	if (get_dir(prev_b, to_find, curr_dir))
	{
		ft_strdel(&to_find);
		to_find = ft_strdup(prev_b);
	}
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
**		Return FAILURE(-1) to stop reading
*/

int8_t			read_dir(char **prev_b, char *to_find, t_read *term)
{
	struct dirent	*data;
	DIR				*dir;
	char			*path;
	char			current_dir[BUFF_SIZE];

	path = NULL;
	if ((dir = update_curr_dir(to_find, *prev_b, current_dir)) == NULL)
		return (FAILURE);
	while ((data = readdir(dir)) != NULL)
	{
		if (isstart(data->d_name, to_find))
		{
			term->found = TRUE;
			path = ft_strjoin(current_dir, data->d_name);
			if (read_again(prev_b, path, data->d_name, term) == TRUE)
				continue ;
			else
			{
				closedir(dir);
				ft_strdel(&path);
				return (FAILURE);
			}
		}
	}
	ft_strdel(&path);
	return (term->found);
}

/*
**		To complete files if char inserted match with any files in current dir
*/

void			to_complete_buffer(char *to_find, t_read *term)
{
	char		*prev_b;

	prev_b = ft_strdup(to_find);
	term->found = FALSE;
	if (isstart(to_find, "$"))
	{
		parse_env(&prev_b, to_find, term);
		ft_strdel(&prev_b);
		return ;
	}
	if (read_dir(&prev_b, to_find, term) == FAILURE)
		return ;
	term->found == TRUE ? to_complete_buffer(to_find, term) : 0;
}
