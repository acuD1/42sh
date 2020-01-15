/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:59:52 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/15 21:24:19 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include "sh42.h"

static int8_t	check_filepath(char *filepath)
{
	int			ret;

	if ((ret = ft_access(filepath, F_OK | X_OK)) != SUCCESS)
		return (ret);
	if (is_dir(filepath))
		return (EISDIR);
	return (SUCCESS);
}

static int8_t	format_path(char *path, t_process *process)
{
	char	*tmp;
	int		i;

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

static int8_t	get_bin_path(t_core *shell, t_process *process)
{
	t_db	*db;
	char	**split_path;
	int		i;

	i = 0;
	if (!(db = search_db(shell->env, "PATH")))
		return (1);
	if (!(split_path = ft_strsplit(db->value, ":")))
		return (FAILURE);
	while (split_path[i] != NULL)
	{
		if (format_path(split_path[i], process) != SUCCESS)
			return (FAILURE);
		if (check_filepath(process->bin) == SUCCESS)
		{
			add_hash_map(shell, process);
			ft_tabdel(&split_path);
			return (SUCCESS);
		}
		ft_strdel(&process->bin);
		i++;
	}
	ft_tabdel(&split_path);
	return (1);
}

int8_t			get_bin(t_core *shell, t_process *process)
{
	int		ret;

	ret = 0;
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
	if ((ret = get_bin_path(shell, process)) == 1)
		return (FAILURE);
	return (SUCCESS);
}
