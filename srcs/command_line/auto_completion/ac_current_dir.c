/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_current_dir.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 17:26:59 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/26 10:25:43 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
** Return only TRUE if tab key is pressed
*/

uint8_t			is_tab(char *buff, char *d_name, t_read *term)
{
	uint64_t	value;

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
			if (check_caps(buff, term) == FALSE)
				xtputs(term->tcaps[KEY_UP], 1, my_outc);
			return (FALSE);
		}
	}
	return (FALSE);
}

int				is_dot(char *d_name)
{
	if (!ft_strcmp(d_name, "."))
		return (TRUE);
	else if (!ft_strcmp(d_name, ".."))
		return (TRUE);
	return (FALSE);
}

char			*get_current_dir(char *curr_dir, char *tmp_curr, t_read *term)
{
	if (term->ac > 1 && is_dir(curr_dir))
		ft_strcpy(tmp_curr, curr_dir);
	else
	{
		if (!getcwd(tmp_curr, BUFF_SIZE))
			return (NULL);
		ft_strcat(tmp_curr, "/");
	}
	return (tmp_curr);
}

/*
**		Display all files in current directory if no any char is inserted
*/

void			display_current_directory(char *buf, t_read *term, char *curr_dir)
{
	struct dirent	*data;
	DIR				*dir;
	char			tmp[BUFF_SIZE];
	char			current_dir[BUFF_SIZE];

	get_current_dir(curr_dir, current_dir, term);
	if ((dir = opendir(current_dir)) == NULL)
		return ;
	ft_strcpy(tmp, current_dir);
	while ((data = readdir(dir)) != NULL)
	{
		if (is_dot(data->d_name) == FALSE)
		{
			ft_strcat(tmp, data->d_name);
			if (is_dir(tmp) == TRUE)
				ft_strcat(data->d_name, "/");
			insert_str_in_buffer(data->d_name, term);
			ft_strcpy(tmp, current_dir);
		}
		else
			continue ;
		if (is_tab(buf, data->d_name, term) == TRUE)
			continue ;
		else
		{
			closedir(dir);
			return ;
		}
	}
	display_current_directory(buf, term, curr_dir);
}
