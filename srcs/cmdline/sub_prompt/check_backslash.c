/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:44:01 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/08 16:23:13 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t	charset_count(t_read *term, char c, size_t i)
{
	u_int8_t	count;

	count = 0;
	while (term->buffer[i])
	{
		if (term->buffer[i] == c)
			count++;
		else if (c == BACKSLASH && count > 0 && term->buffer[i] != c)
			count = 0;
		i++;
	}
	return (count);
}

u_int8_t	check_backslash(t_read *term, char *quote)
{
	if (!*term->buffer)
		return (FALSE);
	if (term->buffer[ft_strlen(term->buffer) - 1] == BACKSLASH)
	{
		if (charset_count(term, BACKSLASH, 0) % 2 != 0)
		{
			*quote = BACKSLASH;
			return (TRUE);
		}
	}
	return (FALSE);
}
