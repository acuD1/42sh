/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:32:18 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/28 08:19:12 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <dirent.h>

static void		fill_file_lst(char *path, char *cmd, DIR *dir, t_auto_comp *ac)
{
	struct dirent	*data;
	char			*tmp;
	ssize_t			len;

	tmp = NULL;
	ac->lst_size = 0;
	len = (ssize_t)ft_strlen(cmd);
	while ((data = readdir(dir)) != NULL)
	{
		if (is_dot(data->d_name) && (len > 0 && cmd[len - 1] != '.'))
			continue ;
		else
			tmp = ft_strjoin(path, data->d_name);
		if (ft_isstart(tmp, cmd))
			ac_add_content(ac, tmp, data->d_name);
		ft_strdel(&tmp);
	}
}

static void		fill_dir_lst(char *path, char *cmd, DIR *dir, t_auto_comp *ac)
{
	struct dirent	*data;
	char			*tmp;
	ssize_t			len;

	tmp = NULL;
	ac->lst_size = 0;
	len = (ssize_t)ft_strlen(cmd);
	while ((data = readdir(dir)) != NULL)
	{
		if (is_dot(data->d_name) && (len > 0 && cmd[len - 1] != '.'))
			continue ;
		else
			tmp = ft_strjoin(path, data->d_name);
		if (ft_isstart(tmp, cmd) && (is_dir(tmp) || is_exec(tmp)))
			ac_add_content(ac, tmp, data->d_name);
		ft_strdel(&tmp);
	}
}

static int8_t	filenames_cmp(char *input, char *path)
{
	struct dirent	*data;
	DIR				*dir;
	ssize_t			len;

	len = (ssize_t)ft_strlen(input);
	if (len > 0 && input[len - 1] == '/')
		return (FAILURE);
	if ((dir = opendir(path)) != NULL)
	{
		while ((data = readdir(dir)) != NULL)
		{
			if (is_dot(data->d_name) && (len > 0 && input[len - 1] != '.'))
				continue ;
			if (ft_isstart(data->d_name, input))
			{
				closedir(dir);
				return (SUCCESS);
			}
		}
	}
	closedir(dir);
	return (FAILURE);
}

static void		check_dir(char *input, char *cmd, char *path, t_auto_comp *ac)
{
	DIR		*dir;
	t_core	*shell;

	shell = get_core(NULL);
	if (filenames_cmp(input, path) != SUCCESS && (dir = opendir(cmd)) != NULL)
	{
		ft_strdel(&path);
		path = ft_strdup(cmd);
		if (!ft_strchr(shell->term.buffer, ' '))
			fill_dir_lst(path, cmd, dir, ac);
		else
			fill_file_lst(path, cmd, dir, ac);
	}
	else if ((dir = opendir(path)) != NULL)
	{
		if (!ft_strchr(shell->term.buffer, ' '))
			fill_dir_lst(path, cmd, dir, ac);
		else
			fill_file_lst(path, cmd, dir, ac);
	}
	ft_strdel(&path);
	closedir(dir);
}

void			ac_file(char *input, t_auto_comp *ac, t_core *shell)
{
	char	*path;
	char	*cmd;

	(void)shell;
	path = NULL;
	ac->ws_col = (size_t)shell->term.ws_col;
	cmd = get_dir_path(ac, input, &path);
	check_dir(input, cmd, path, ac);
	ft_strdel(&cmd);
}
