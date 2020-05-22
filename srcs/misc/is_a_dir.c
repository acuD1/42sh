/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:25:39 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/07 02:10:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>
#include <errno.h>

int8_t	is_a_dir(const char *path)
{
	struct stat	stat;

	if (lstat(path, &stat) != 0)
		return (FAILURE);
	if (S_ISDIR(stat.st_mode))
		return (EISDIR);
	return (ENOTDIR);
}
