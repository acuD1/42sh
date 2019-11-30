/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:44:01 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/30 17:52:59 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		charset_count(t_read *input, char c, int i)
{
	int	count;

	count = 0;
	while (input->buffer[i])
	{
		if (input->buffer[i] == c)
			count++;
		else if (c == BACKSLASH && count > 0 && input->buffer[i] != c)
			count = 0;
		i++;
	}
	return (count);
}

uint8_t		check_backslash(t_read *input, char *quote)
{
	if (input->buffer[ft_strlen(input->buffer) - 1] == BACKSLASH)
	{
		if (input->buffer[ft_strlen(input->buffer) - 1] != BACKSLASH)
			return (FALSE);
		if (charset_count(input, BACKSLASH, 0) % 2 != 0)
		{
			if (ft_strlen(input->buffer) > 1)
				input->buffer = ft_strjoin(input->buffer, ";");
			*quote = BACKSLASH;
			return (TRUE);
		}
	}
	return (FALSE);
}
