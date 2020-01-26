/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 01:59:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/15 16:43:18 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Update [INTERNAL_VAR] PISTASH_VERSION variable, containing the version
**	informations of the current shell
**		- Should only be executed at shell startup
*/

int8_t	update_version(t_core *shell)
{
	t_db	*db;
	char	version[32];
	char	*value;

	db = NULL;
	value = NULL;
	ft_bzero(version, 32);
	ft_strcat(version, "'");
	ft_itoabuf(shell->build.release, version);
	ft_strcat(version, ".");
	ft_itoabuf(shell->build.version, version);
	ft_strcat(version, ".");
	ft_itoabuf(shell->build.patch, version);
	ft_strcat(version, "-dev'");
	if (shell != NULL
		&& (db = get_or_create_db(shell, "SH_VERSION", INTERNAL_VAR)) != NULL)
	{
		value = ft_strdup(version);
		if (value && modify_db(db, value, 0) != NULL)
			return (SUCCESS);
		ft_strdel(&value);
	}
	return (FAILURE);
}
