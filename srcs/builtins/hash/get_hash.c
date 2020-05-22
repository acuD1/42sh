/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hash.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/02 15:01:50 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/06 17:24:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int32_t	get_hash(const char *line, u_int32_t size)
{
	size_t		i;
	u_int32_t	hash;

	i = 0;
	hash = 0;
	while (i < ft_strlen(line))
	{
		hash = ((hash << 8) + (u_int8_t)line[i]) % size;
		i++;
	}
	return (hash);
}
