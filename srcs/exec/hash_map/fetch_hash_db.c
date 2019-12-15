/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_hash_db.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:57:11 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/15 15:04:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_db	*fetch_hash_db
	(t_db *db, const char *key, const char *value,  u_int8_t format)
{
	db->key = ft_strdup(key);
	db->value = ft_strdup(value);
	if (format & HASH_DEFAULT)
		db->hit = 1;
	if (format & HASH_PATH)
		db->hit = 0;
	return (db);
}
