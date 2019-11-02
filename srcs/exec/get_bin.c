/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_bin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/22 12:59:52 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/02 21:29:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static int8_t	check_filepath(t_core *shell, t_lst *process)
{
	int			ret;

	if ((ret = ft_access(((t_process*)process->content)->av[0], F_OK | X_OK)) != SUCCESS)
		return (ret);
	if (is_dir(((t_process*)process->content)->av[0]))
		return (EISDIR);
	return (SUCCESS);
}

statis int8_t	format_path(char *path, char *filename, char **result)
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

static int8_t	get_bin_path(t_core *shell, t_lst *process)
{
	t_lst	*db;
	char	**split_path;
	char	*bin_path;
	int		i;

	i = 0;
	bin_path = NULL;
	if (!(db = search_db(shell, "PATH")))
		return (1);
	if (!(split_path = ft_strsplit(((t_db*)(env->content))->value, ":")))
		return (FAILURE);
	while (split_path[i] != NULL)
	{
		if (format_path(split_path[i], ((t_process*)process->content)->av[0], &bin_path) != SUCCESS)
			return (FAILURE);
		if (ft_access(bin_path, F_OK | X_OK) == SUCCESS && is_a_dir(bin_path) != SUCCESS)
		{
			((t_process*)process->content)->bin = bin_path;
			ft_tabdel(&split_path);
			return (SUCCESS);
		}
		ft_strdel(&bin_path);
		i++;
	}
	ft_tabdel(&split_path);
	return (1);
}

int8_t	get_bin(t_core *shell, t_lst *process)
{
	int		ret;

	ret = 0;
	/*
	**	We set the shell->bin variable if process->content->av[0] is a local binary here
	*/
	if ((((t_process*)process->content)->av[0][0] == '.'
			&& ((t_process*)process->content)->av[0][1] == '/'
			&& ((t_process*)process->content)->av[0][2] != 0)
		|| (((t_process*)process->content)->av[0][0] == '/'
			&& ((t_process*)process->content)->av[0][1]))
		process->bin = ft_strdup(shell->tokens[0]);
	else
	{
		/*
		**	HASH_TABLE : Locate process->contntav[0] in the hash_map first, if found retourn the path found !
		** NEED TO  CHECK THAT THE FILE IS STILL EXECUTABLE (existing + x etc)
		*/
		if (locate_hash(shell, process) == SUCCESS && check_filepath(shell, process) == SUCCESS)
			return (SUCCESS);
		if ((ret = get_bin_path(shell, process)) == 1)
			return (1);
	}
	/*
	** NEED TO RETURN PROPER VALUE (-1 FAILURE | 0 command found  | 1 command not found)
	*/
	ret = check_filepath(shell, process);
	//update_hashmap(...);
	ft_perror("bash", ret);
	return ()
}
