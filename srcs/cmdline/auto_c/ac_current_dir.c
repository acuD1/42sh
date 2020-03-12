/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_current_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:59 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/12 02:39:39 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include "sh42.h"

/*
** Return only TRUE if tab key is pressed
*/

u_int8_t		is_tab(const char *d_name, t_read *term)
{
	u_int64_t	value;
	char		buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	if (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		value = get_mask(buff);
		if (value == TAB_KEY)
		{
			delete_last_cmd(d_name, term);
			return (TRUE);
		}
		else
		{
			term->ac_tmp = ft_strdup(buff);
			return (FALSE);
		}
	}
	return (FALSE);
}

u_int8_t		is_dot(const char *d_name)
{
	if (!ft_strcmp(d_name, "."))
		return (TRUE);
	else if (!ft_strcmp(d_name, ".."))
		return (TRUE);
	return (FALSE);
}

static int8_t	get_dir(t_read *term, const char *av, char *new_dir)
{
	if (!getcwd(new_dir, BUFF_SIZE))
		return (FAILURE);
	if (term->ac > 1 && is_dir(av))
	{
		ft_strcpy(new_dir, av);
		if (av[ft_strlen(av) - 1] != '/')
			insert_in_buffer("/", term);
		return (SUCCESS);
	}
	return (SUCCESS);
}

static int8_t	read_curr_dir
	(t_read *term, char tmp[], const char curr[], DIR *dir)
{
	struct dirent	*data;

	while ((data = readdir(dir)) != NULL)
	{
		term->flag++;
		if (is_dot(data->d_name) == FALSE)
		{
			ft_strcat(tmp, "/");
			ft_strcat(tmp, data->d_name);
			if (is_dir(tmp) == TRUE)
				ft_strcat(data->d_name, "/");
			insert_str_in_buffer(data->d_name, term);
			ft_strcpy(tmp, curr);
		}
		else
			continue ;
		if (is_tab(data->d_name, term) == TRUE)
			continue ;
		else
		{
			closedir(dir);
			return (FAILURE);
		}
	}
	return (TRUE);
}

/*
**		Display all files in current directory if no any char is inserted
*/

void			display_current_directory(t_read *term, const char *av)
{
	DIR		*dir;
	char	tmp[BUFF_SIZE];
	char	new_dir[BUFF_SIZE];

	term->flag = FALSE;
	if (get_dir(term, av, new_dir) == FAILURE)
		return ;
	if ((dir = opendir(new_dir)) == NULL)
		return ;
	ft_strcpy(tmp, new_dir);
	if (read_curr_dir(term, tmp, new_dir, dir) == FAILURE)
		return ;
	closedir(dir);
	if (term->flag != 2)
		display_current_directory(term, av);
}
