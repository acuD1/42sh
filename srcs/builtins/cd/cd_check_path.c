/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_check_path.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 17:14:23 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/10 18:39:47 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <errno.h>

int8_t		cd_check_path(const char *path)
{
	int8_t	errnum;

	errnum = 0;
	if (access(path, F_OK) == 0)
		errnum = is_a_dir(path);
	errnum = (errnum == EISDIR) ? 0 : errnum;
	if (errnum == 0)
		errnum = ft_access(path, X_OK);
	return (errnum);
}
