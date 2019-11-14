/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_a_dir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:25:39 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/05 01:43:34 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

int8_t	is_a_dir(char *path)
{
	struct stat	stat;

	if ((lstat(path, &stat) == 0 && S_ISDIR(stat.st_mode)))
		return (SUCCESS);
	return (FAILURE);
}
