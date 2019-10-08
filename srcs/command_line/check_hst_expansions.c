/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hst_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:03:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/08 15:19:35 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		find_expansions(t_read *line, int *i)
{
	if (line->buffer[*i + 1] == '!')
		last_cmd_back(line, *i);
	else if (ft_isdigit(line->buffer[*i + 1]))
		call_number(line, *i);
	else if (ft_isalpha(line->buffer[*i + 1]))
		call_word(line, *i);
	else if (line->buffer[*i + 1] == '-' && ft_isdigit(line->buffer[*i + 2]))
		callback_number(line, *i);
}

void		check_expansions(t_read *line)
{
	int		i;
	int		buff_len;

	i = -1;
	buff_len = ft_strlen(line->buffer);
	while (buff_len--)
	{
		if (line->buffer[++i] == '!')
			find_expansions(line, &i);
	}
}
