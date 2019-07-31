/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_db.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/20 17:13:44 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/20 17:15:24 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	fetch_db format char **environ into {key} and {value}
*/

t_db	*fetch_db(t_db *db, const char *s)
{
	size_t	len;

	len = ft_strclen(s, '=');
	db->key = ft_strsub(s, 0, len);
	db->value = ft_strdup(s + len + 1);
	return (db);
}
