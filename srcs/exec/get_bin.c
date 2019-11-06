/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:59:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/07 00:42:34 by mpivet-p         ###   ########.fr       */
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

static int8_t	format_path(char *path, char *filename, char **result)
{
	char	*tmp;
	int		i;

	i = ft_strlen(path);
	tmp = NULL;
	if (i > 0 && path[i - 1] == '/')
	{
		if ((*result = ft_strjoin(path, filename)) == NULL)
			return (FAILURE);
		return (SUCCESS);
	}
	if (!(tmp = ft_strjoin("/", filename)))
		return (FAILURE);
	*result = ft_strjoin(path, tmp);
	ft_strdel(&tmp);
	return ((*result == NULL) ? FAILURE : SUCCESS);
}

static int8_t	get_bin_path(t_core *shell, t_process *process)
{
	t_db	*db;
	char	**split_path;
	char	*bin_path;
	int		i;

	i = 0;
	bin_path = NULL;
	if (!(db = search_db(shell->env, "PATH")))
		return (1);
	if (!(split_path = ft_strsplit(db->value, ":")))
		return (FAILURE);
	while (split_path[i] != NULL)
	{
		if (format_path(split_path[i], process->av[0], &bin_path) != SUCCESS)
			return (FAILURE);
		if (check_filepath(bin_path) == SUCCESS)
		{
			process->bin = bin_path;
			ft_tabdel(&split_path);
			return (SUCCESS);
		}
		ft_strdel(&bin_path);
		i++;
	}
	ft_tabdel(&split_path);
	return (1);
}

int8_t	get_bin(t_core *shell, t_process *process)
{
	int		ret;

	ret = 0;
	/*
	**	We set the shell->bin variable if process->content->av[0] is a local binary here
	*/
	if ((process->av[0][0] == '.'
			&& process->av[0][1] == '/'
			&& process->av[0][2] != 0)
		|| (process->av[0][0] == '/'
			&& process->av[0][1]))
		process->bin = ft_strdup(process->av[0]);
	else
	{
		/*
		**	HASH_TABLE : Locate process->contntav[0] in the hash_map first,
		**	if found retourn the path found !
		**	NEED TO  CHECK THAT THE FILE IS STILL EXECUTABLE (existing + x etc)
		**	DISABLED TILL HASHMAP REWORK
		if (locate_hash(shell, process) == SUCCESS && check_filepath(shell, process) == SUCCESS)
			return (SUCCESS);
		*/
		if ((ret = get_bin_path(shell, process)) == 1)
			return (FAILURE);
	}
	if (process->bin && (ret = check_filepath(process->bin)) != SUCCESS)
	{
		ft_perror(process->av[0], ret);
		exit(127);
	}
	//update_hashmap(...);
	return (SUCCESS);
}
