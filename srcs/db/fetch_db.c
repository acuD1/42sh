/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_db.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:13:44 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/12 13:40:10 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	fetch_db format char **environ into {key}, {value}
**	and {var_type} (env, set or intern)
*/

t_db	*fetch_db(t_db *db, const char *s, u_int8_t var_type)
{
	size_t	len;

	len = ft_strclen(s, '=');
	ft_bzero(db, sizeof(t_db));
	if (!(db->key = ft_strsub(s, 0, len)))
		return (NULL);
	if (ft_strchr(s, '='))
		if (!(db->value = ft_strsub(s,
			(unsigned int)len + 1, ft_strlen(s) - len)))
		{
			ft_strdel(&(db->key));
			return (NULL);
		}
	db->type = var_type;
	return (db);
}
