/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_access.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/15 00:18:54 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/05/30 18:08:31 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>
#include <errno.h>
#include <unistd.h>

static u_int8_t	access_file(const char *path, char *prev, u_int32_t mode)
{
	struct stat	file;
	size_t		len;

	if (stat(path, &file) < 0)
	{
		if ((len = ft_strlen(path)) - ft_strlen(prev) == 1
		&& path[len - 1] == '/')
			return (ENOTDIR);
		return (ENOENT);
	}
	if (file.st_mode & ((mode & 07) << 6))
	{
		ft_strcpy(prev, path);
		return (SUCCESS);
	}
	return (EACCES);
}

static size_t	dir_depth(const char *path, char *buffer, size_t depth)
{
	const char	*ptr;
	ssize_t		i;

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
	ft_strncpy(buffer, path, (size_t)i);
	return (ft_strlen(buffer));
}

int8_t			ft_access(const char *path, u_int8_t mode)
{
	char	buffer[MAX_PATH + 1];
	char	prev[MAX_PATH + 1];
	size_t	path_len;
	size_t	depth;
	int8_t	ret;

	depth = 0;
	if (access(path, mode) == 0)
		return (SUCCESS);
	ft_bzero(buffer, MAX_PATH + 1);
	getcwd(buffer, MAX_PATH);
	if (ft_strlen(path) + ft_strlen(buffer) > ACCESS_MAX_PATH
			|| get_canonical_path(NULL, path, buffer, NULL) != SUCCESS)
		return (ENAMETOOLONG);
	path_len = ft_strlen(buffer);
	ft_bzero(prev, MAX_PATH + 1);
	while (dir_depth(path, buffer, ++depth) <= path_len + 1)
	{
		if ((ret = (int8_t)access_file(buffer, prev, F_OK | X_OK)) != SUCCESS)
		{
			ft_bzero(buffer, MAX_PATH + 1);
			return (ret);
		}
	}
	return ((int8_t)access_file(buffer, prev, mode));
}
