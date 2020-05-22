/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:59:52 by arsciand          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:30 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>
#include <unistd.h>

static int8_t	check_filepath(const char *filepath)
{
	int8_t	ret;

	if ((ret = ft_access(filepath, F_OK | X_OK)) != SUCCESS)
		return (ret);
	if (is_dir(filepath))
		return (EISDIR);
	return (SUCCESS);
}

static int8_t	format_path(const char *path, t_process *process, char **tpath)
{
	char	*tmp;
	size_t	i;

	i = ft_strlen(path);
	tmp = NULL;
	if (i > 0 && path[i - 1] == '/')
	{
		if ((*tpath = ft_strjoin(path, process->av[0])) == NULL)
			return (FAILURE);
		return (SUCCESS);
	}
	if (!(tmp = ft_strjoin("/", process->av[0])))
		return (FAILURE);
	*tpath = ft_strjoin(path, tmp);
	ft_strdel(&tmp);
	return ((*tpath == NULL) ? FAILURE : SUCCESS);
}

static int8_t	valid_path(t_process *process, char ***splt_path, char **path)
{
	if (access(*path, F_OK) == 0)
	{
		ft_strdel(&(process->bin));
		process->bin = ft_strdup(*path);
		if (check_filepath(process->bin) == SUCCESS)
		{
			ft_strdel(path);
			ft_tabdel(splt_path);
			return (SUCCESS);
		}
	}
	ft_strdel(path);
	return (FAILURE);
}

int8_t			get_bin_path(t_core *shell, t_process *ptr)
{
	char	**split_path;
	char	*path;
	t_db	*db;
	ssize_t	i;

	i = -1;
	path = NULL;
	if ((db = search_db(shell->env, "PATH")) == NULL)
		return (ptr->blt || !(ptr->bin = ft_strdup(ptr->av[0])) ? -1 : 0);
	if (!(split_path = ft_strsplit(db->value, ":")))
		return (FAILURE);
	while (split_path[++i] != NULL)
	{
		if (access(split_path[i], X_OK | F_OK) == 0)
		{
			if (format_path(split_path[i], ptr, &path) != SUCCESS)
				return (FAILURE);
			if (path && valid_path(ptr, &split_path, &path) == SUCCESS)
				return (SUCCESS);
		}
	}
	ft_tabdel(&split_path);
	return (1);
}

int8_t			get_bin(t_core *shell, t_process *process)
{
	int8_t	ret;

	ret = 0;
	if (process->av[0][0] == 0)
	{
		process->bin = NULL;
		return (SUCCESS);
	}
	if ((process->av[0][0] == '.'
		&& (process->av[0][1] == '/'
			|| (process->av[0][1] == '.' && process->av[0][2])))
		|| (process->av[0][0] == '/'))
	{
		process->bin = ft_strdup(process->av[0]);
		return (SUCCESS);
	}
	if (!shell->opt && locate_hash(shell, process) == SUCCESS)
		return (SUCCESS);
	ret = get_bin_path(shell, process);
	if (!shell->opt && !process->blt)
		hash_dispatcher(shell, process, H_EXEC);
	if (ret == 1)
		return (FAILURE);
	return (SUCCESS);
}
