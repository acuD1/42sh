/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 01:59:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/25 02:24:43 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	update_version(t_core *core)
{
	t_db	*db;
	char	version[32];

	db = NULL;
	ft_bzero(version, 32);
	ft_strcat(version, "'");
	ft_itoabuf(core->build.release, version);
	ft_strcat(version, ".");
	ft_itoabuf(core->build.version, version);
	ft_strcat(version, ".");
	ft_itoabuf(core->build.patch, version);
	ft_strcat(version, "-proto'");
	if (core && (db = get_or_create_db(core, "PISTASH_VERSION", SET_VAR)) != NULL)
	{
		if (modify_db(db, version, 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}
