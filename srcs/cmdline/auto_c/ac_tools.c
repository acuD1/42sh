/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 15:13:52 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/29 11:46:32 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

u_int8_t	last_is_slash(char *str)
{
	size_t		i;

	i = ft_strlen(str);
	if (str[i - 1] != '/')
	{
		if (str[i - 1] == '.')
		{
			if (i >= 2 && str[i - 2] == '.')
				return (FALSE);
			else
				return (TRUE);
		}
		return (FALSE);
	}
	return (TRUE);
}

u_int8_t	is_exec(char *path)
{
	struct stat		tmp;

	if (access(path, F_OK) == FAILURE)
		return (FALSE);
	if (stat(path, &tmp) == SUCCESS)
	{
		if (S_ISREG(tmp.st_mode) && access(path, X_OK) == SUCCESS)
			return (TRUE);
	}
	return (FALSE);
}

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

size_t		get_max_len(size_t len, size_t new_len)
{
	if (len >= new_len)
		return (len);
	return (new_len);
}
