/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:13:52 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/08 00:43:59 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

u_int8_t	is_dir(const char *dir)
{
	struct stat	buf;
	char		*tmp;

	if (!*dir || !dir)
		return (FALSE);
	if (!ft_isstart(dir, "/"))
		tmp = ft_strjoin("./", dir);
	else
		tmp = ft_strdup(dir);
	if (lstat(dir, &buf) == FAILURE)
	{
		ft_strdel(&tmp);
		return (FALSE);
	}
	if (S_ISDIR(buf.st_mode) && !is_dot(dir))
	{
		ft_strdel(&tmp);
		return (TRUE);
	}
	ft_strdel(&tmp);
	return (FALSE);
}

u_int8_t	is_dot(const char *d_name)
{
	if (!ft_strcmp(d_name, "."))
		return (TRUE);
	else if (!ft_strcmp(d_name, ".."))
		return (TRUE);
	return (FALSE);
}

/*
**		Split all bin/sbin directories in an array
*/

char		**split_path(t_core *shell, const char *str)
{
	char	**array;
	t_lst	*env;

	env = shell->env;
	array = NULL;
	while (env)
	{
		if (!ft_strcmp(str, ((t_db*)(env->content))->key))
		{
			array = ft_strsplit(((t_db*)(env->content))->value, ":");
			break ;
		}
		env = env->next;
	}
	return (array);
}

size_t		get_max_len(size_t len, size_t new_len)
{
	if (len >= new_len)
		return (len);
	return (new_len);
}
