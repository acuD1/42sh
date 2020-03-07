/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_buffer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:30 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/07 17:19:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "sh42.h"

/*
**		Delete last command insert in buffer and insert the new one
**		Read again buff if another tab key is pressed => return TRUE
*/

u_int8_t		read_again
	(char **prev, const char *path, char *name, t_read *term)
{
	u_int64_t	value;
	char		buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	delete_last_cmd(*prev, term);
	if (path && is_dir(path) == TRUE)
		ft_strcat(name, "/");
	insert_str_in_buffer(name, term);
	if (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		if (value == TAB_KEY)
		{
			ft_strdel(&*prev);
			*prev = ft_strdup(name);
			return (TRUE);
		}
		else
		{
			term->ac_tmp = ft_strdup(buff);
			term->flag = FALSE;
			return (FALSE);
		}
	}
	return (FALSE);
}

static u_int8_t	get_dir(t_read *term, char *current_dir)
{
	size_t	found;
	char	*tmp;
//	int		i;

	//i = 0;
	tmp = NULL;
	found = ft_strlen(term->cmd[0]);
	while (found--)
	{
		if (term->cmd[0][found] == '/')
		{
			ft_bzero(current_dir, BUFF_SIZE);
			ft_strncpy(current_dir, term->cmd[1], found + 1);
			tmp = ft_strdup(ft_strrchr(term->cmd[0], '/'));
			ft_strdel(&term->cmd[0]);
		//	i = ft_strlen(tmp);
			term->cmd[0] = ft_strdup(tmp + 1);
			ft_strdel(&tmp);
			return (TRUE);
		}
	}
	return (FALSE);
}

static DIR		*update_curr_dir(t_read *term, char *curr_dir)
{
	DIR		*dir;
	char	*tmp;

	tmp = NULL;
	if (get_dir(term, curr_dir))
	{
		tmp = ft_strdup(term->cmd[0]);
		ft_strdel(&term->cmd[1]);
		term->cmd[1] = ft_strdup(tmp);
		ft_strdel(&tmp);
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

static void		read_dir(t_read *term, char const current_dir[], DIR *dir)
{
	struct dirent	*data;
	char			*path;

	path = NULL;
	while ((data = readdir(dir)) != NULL)
	{
		ft_strdel(&path);
		if (ft_isstart(data->d_name, term->cmd[0]))
		{
			term->flag = TRUE;
			path = ft_strjoin(current_dir, data->d_name);
			if (read_again(&term->cmd[1], path, data->d_name, term) == TRUE)
				continue ;
			else
				break ;
		}
	}
	ft_strdel(&path);
	closedir(dir);
	if (term->flag == TRUE)
	{
		if ((dir = opendir(current_dir)) == NULL)
			return ;
		read_dir(term, current_dir, dir);
	}
}

/*
**		To complete files if char inserted match with any files in current dir
*/

void			to_complete_buffer(const char *to_find, t_read *term)
{
	char	current_dir[BUFF_SIZE];
	DIR		*dir;
//	int		brace;

//	brace = 0;
	ft_bzero(current_dir, BUFF_SIZE);
	term->flag = FALSE;
	ft_tabfree(term->cmd);
	term->cmd = ft_memalloc(BUFF_SIZE);
	term->cmd[0] = ft_strdup(to_find);
	term->cmd[1] = ft_strdup(to_find);
	if (ft_isstart(to_find, "$") || ft_isstart(to_find, "${"))
	{
		parse_env(&term->cmd[1], term->cmd[0], term);
		return ;
	}
	if ((dir = update_curr_dir(term, current_dir)) == NULL)
		return ;
	read_dir(term, current_dir, dir);
}
