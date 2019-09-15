/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_db.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:13:44 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/15 19:01:54 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	fetch_db format char **environ into {key}, {value}
**	and {var_type} (env, set or intern)
*/

t_db	*fetch_db(t_db *db, const char *s, const u_int8_t var_type)
{
	size_t	len;

	len = ft_strclen(s, '=');
	db->key = ft_strsub(s, 0, len);
	db->value = ft_strdup(s + len + 1);
	db->type = var_type;
	return (db);
}
