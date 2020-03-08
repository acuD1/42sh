/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_use_cd_path.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 13:53:40 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 14:31:06 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static int8_t	use_cd_path_handler
	(t_core *shell, char *dir, char *path, char **tab)
{
	ft_dprintf(STDERR_FILENO, "%s\n", dir);
	update_pwds(shell, (char *)dir, path);
	ft_strdel(&dir);
	ft_tabdel(&tab);
	return (SUCCESS);
}

static char		*choose_dir(t_core *shell, char **tab, size_t i)
{
	t_db	*pwd;
	char	*dir;

	dir = NULL;
	pwd = NULL;
	if (ft_strequ(tab[i], ".") == TRUE)
	{
		if ((pwd = search_db(shell->env, "PWD")) == NULL)
		{
			ft_tabdel(&tab);
			return (NULL);
		}
		dir = ft_strdup(pwd->value);
	}
	else
		dir = ft_strdup(tab[i]);
	return (dir);
}

int8_t			cd_use_cd_path(t_core *shell, const char *path)
{
	t_db	*cdpath;
	char	**tab;
	char	*dir;
	size_t	i;

	cdpath = NULL;
	if (path[0] != '/' && ft_strequ(path, "..") == FALSE
		&& shell && (cdpath = search_db(shell->env, "CDPATH")) != NULL)
	{
		tab = ft_strsplit(cdpath->value, ":");
		i = 0;
		while (tab[i])
		{
			if ((dir = choose_dir(shell, tab, i)) == NULL)
				return (FAILURE);
			dir = ft_strjoinf(dir, "/", 1);
			dir = ft_strjoinf(dir, (char *)path, 1);
			if (chdir(dir) == SUCCESS)
				return (use_cd_path_handler(shell, dir, (char *)path, tab));
			ft_strdel(&dir);
			i++;
		}
		ft_tabdel(&tab);
	}
	return (FAILURE);
}
