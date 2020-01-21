/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_hash_db.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:57:11 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/13 08:31:06 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_db	*fetch_hash_db
	(t_db *db, const char *key, const char *value, enum e_hash fmt)
{
	if (!(db->key = ft_strdup(key)))
		return (NULL);
	if (!(db->value = ft_strdup(value)))
		return (NULL);
	if (fmt == H_EXEC)
		db->hit = 1;
	if (fmt == H_PATH)
		db->hit = 0;
	return (db);
}
