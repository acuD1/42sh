/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 00:18:54 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/07 04:07:53 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include "sys/stat.h"
#include "errno.h"

static int8_t	access_file(const char *path, int mode)
{
	struct stat	file;

	if (stat(path, &file) < 0)
	{
		return (ENOENT);
	}
	if (file.st_mode & ((mode & 07) << 6))
		return (SUCCESS);
	return (EACCES);
}

static int32_t	dir_depth(const char *path, char *buffer, int depth)
{
	const char	*ptr;
	int			i;

	i = 0;
	ptr = path;
	ft_bzero(buffer, MAX_PATH);
	if (depth == 0)
		return (ft_strlen(ft_strcpy(buffer, "/")));
	while (depth)
	{
		if ((ptr = ft_strchr(ptr + 1, '/')) == NULL)
		{
			ft_strcpy(buffer, path);
			return (ft_strlen(buffer));
		}
		depth--;
	}
	i = ptr - path;
	ft_strncpy(buffer, path, i);
	return (ft_strlen(buffer));
}

int8_t			ft_access(const char *path, int mode)
{
	char	buffer[MAX_PATH + 1];
	int		path_len;
	int		depth;
	int		ret;

	depth = 0;
	path_len = 0;
	if (access(path, mode) == 0)
		return (SUCCESS);
	ft_bzero(buffer, MAX_PATH + 1);
	getcwd(buffer, MAX_PATH);
	if (ft_strlen(path) + ft_strlen(buffer) > ACCESS_MAX_PATH
			|| get_canonical_path(path, buffer) != SUCCESS)
		return (ENAMETOOLONG);
	path_len = ft_strlen(buffer);
	while (dir_depth(path, buffer, depth) < path_len)
	{
		if ((ret = access_file(buffer, F_OK | X_OK)) != SUCCESS)
		{
			ft_bzero(buffer, MAX_PATH);
			return (ret);
		}
		depth++;
	}
	return (access_file(buffer, mode));
}
