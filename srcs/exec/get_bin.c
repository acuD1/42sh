/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:59:52 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 18:12:21 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"

static int8_t	check_filepath(const char *filepath)
{
	int8_t	ret;

	if ((ret = ft_access(filepath, F_OK | X_OK)) != SUCCESS)
		return (ret);
	if (is_dir(filepath))
		return (EISDIR);
	return (SUCCESS);
}

static int8_t	format_path(const char *path, t_process *process)
{
	char	*tmp;
	size_t	i;

	i = ft_strlen(path);
	tmp = NULL;
	if (i > 0 && path[i - 1] == '/')
	{
		if ((process->bin = ft_strjoin(path, process->av[0])) == NULL)
			return (FAILURE);
		return (SUCCESS);
	}
	if (!(tmp = ft_strjoin("/", process->av[0])))
		return (FAILURE);
	process->bin = ft_strjoin(path, tmp);
	ft_strdel(&tmp);
	return ((process->bin == NULL) ? FAILURE : SUCCESS);
}

static int8_t	valid_path(t_process *process, char ***splt_path)
{
	if (check_filepath(process->bin) == SUCCESS)
	{
		ft_tabdel(splt_path);
		return (SUCCESS);
	}
	if (access(process->bin, F_OK) != 0)
		ft_strdel(&process->bin);
	return (FAILURE);
}

int8_t			get_bin_path(t_core *shell, t_process *process)
{
	char	**split_path;
	t_db	*db;
	size_t	i;

	i = 0;
	if ((db = search_db(shell->env, "PATH")) == NULL)
	{
		return (process->blt || ((process->bin = ft_strdup(process->av[0]))
			== NULL ? FAILURE : SUCCESS));
	}
	if (!(split_path = ft_strsplit(db->value, ":")))
		return (FAILURE);
	while (split_path[i] != NULL)
	{
		ft_strdel(&(process->bin));
		if (access(split_path[i], X_OK | F_OK) == 0)
		{
			if (format_path(split_path[i], process) != SUCCESS)
				return (FAILURE);
			if (valid_path(process, &split_path) == SUCCESS)
				return (SUCCESS);
		}
		i++;
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
			&& process->av[0][1] == '/'
			&& process->av[0][2] != 0)
		|| (process->av[0][0] == '/'
			&& process->av[0][1]))
	{
		process->bin = ft_strdup(process->av[0]);
		return (SUCCESS);
	}
	if (locate_hash(shell, process) == SUCCESS)
		return (SUCCESS);
	ret = get_bin_path(shell, process);
	if (!process->blt)
		hash_dispatcher(shell, process, H_EXEC);
	if (ret == 1)
		return (FAILURE);
	return (SUCCESS);
}
