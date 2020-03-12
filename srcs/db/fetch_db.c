/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_db.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:13:44 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/08 17:13:57 by arsciand         ###   ########.fr       */
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
	db->key = ft_strsub(s, 0, len);
	db->value = ft_strsub(s, (unsigned int)len + 1, ft_strlen(s) - len);
	db->type = var_type;
	if (!db->value || !db->key)
	{
		ft_strdel(&(db->key));
		ft_strdel(&(db->value));
		return (NULL);
	}
	return (db);
}
