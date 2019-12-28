/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_hash_db.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:57:11 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/28 19:08:52 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_db	*fetch_hash_db
	(t_db *db, const char *key, const char *value, u_int8_t format)
{
	if (!(db->key = ft_strdup(key)))
		return (NULL);
	if (!(db->value = ft_strdup(value)))
		return (NULL);
	if (format & HASH_EXEC)
		db->hit = 1;
	if (format & HASH_PATH)
		db->hit = 0;
	return (db);
}
