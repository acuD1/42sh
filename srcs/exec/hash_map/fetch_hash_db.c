/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fetch_hash_db.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 14:57:11 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/14 14:40:29 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_db	*fetch_hash_db(t_db *db,
			const char *key, const char *value, const int hit)
{
	db->key = ft_strdup(key);
	db->value = ft_strdup(value);
	db->hit = hit;
	return (db);
}
