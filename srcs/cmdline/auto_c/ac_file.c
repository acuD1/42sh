/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_file.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:32:18 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/08 01:27:16 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <dirent.h>

static void		ac_add_content(t_auto_comp *ac, char *path, char *d_name)
{
	char		*tmp;

	tmp = NULL;
	if (is_dir(path))
		tmp = ft_strjoin(d_name, "/");
	else
		tmp = ft_strjoin(d_name, " ");
	ft_lstappend(&ac->lst, ft_lstnew(tmp, sizeof(char) * (ft_strlen(tmp) + 1)));
	ac->lst_size++;
	ac->max_len = get_max_len(ac->max_len, ft_strlen(tmp));
	ft_strdel(&tmp);
}

static void		fill_file_lst(char *path, char *cmd, DIR *dir, t_auto_comp *ac)
{
	struct dirent	*data;
	char			*tmp;
	ssize_t			len;

	tmp = NULL;
	ac->lst_size = 0;
	len = ft_strlen(cmd);
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
	len = ft_strlen(cmd);
	while ((data = readdir(dir)) != NULL)
	{
		if (is_dot(data->d_name) && (len > 0 && cmd[len - 1] != '.'))
			continue ;
		else
			tmp = ft_strjoin(path, data->d_name);
		if (ft_isstart(tmp, cmd) && is_dir(tmp))
			ac_add_content(ac, tmp, data->d_name);
		ft_strdel(&tmp);
	}
}

static u_int8_t	filenames_cmp(char *input, char *path)
{
	struct dirent	*data;
	DIR				*dir;
	ssize_t			len;

	len = ft_strlen(input);
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

void			ac_file(char *input, t_auto_comp *ac, t_core *shell)
{
	char	*path;
	char	*cmd;
	DIR		*dir;

	(void)shell;
	path = NULL;
	ac->ws_col = shell->term.ws_col;
	cmd = get_dir_path(ac, input, &path);
	if (filenames_cmp(input, path) != SUCCESS && (dir = opendir(cmd)) != NULL)
	{
		ft_strdel(&path);
		path = ft_strdup(cmd);
		if (!ft_strchr(input, ' '))
			fill_dir_lst(path, cmd, dir, ac);
		else
			fill_file_lst(path, cmd, dir, ac);
	}
	else if ((dir = opendir(path)) != NULL)
		fill_file_lst(path, cmd, dir, ac);
	closedir(dir);
	ft_strdel(&path);
	ft_strdel(&cmd);
}
