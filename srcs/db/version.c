/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   version.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 01:59:58 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/09/29 02:56:43 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Update [SET] PISTASH_VERSION variable, containing the version informations
**	of the current shell
*/

int8_t	update_version(t_core *shell)
{
	t_db	*db;
	char	version[32];

	db = NULL;
	ft_bzero(version, 32);
	ft_strcat(version, "'");
	ft_itoabuf(shell->build.release, version);
	ft_strcat(version, ".");
	ft_itoabuf(shell->build.version, version);
	ft_strcat(version, ".");
	ft_itoabuf(shell->build.patch, version);
	ft_strcat(version, "-dev'");
	if (shell && (db = get_or_create_db(shell, "PISTASH_VERSION", INTERNAL_VAR)) != NULL)
	{
		if (modify_db(db, ft_strdup(version), 0) != NULL)
			return (SUCCESS);
	}
	return (FAILURE);
}
