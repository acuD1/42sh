/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:59:34 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/17 16:35:28 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		callback_number(t_read *line, int i)
{
	int		nb;

	nb = 0;
	while (ft_isdigit(line->buffer[i++]))
		printf("[%d]\n", nb);
}

void		last_cmd_back(t_read *line, int i)
{
	int		j;
	int		len;
	char	*tmp;

	if (!line->history || ft_strlen(line->buffer) > BUFF_SIZE)
		return ;
	j = -1;
	len = line->width - line->prompt_len - 2;
	tmp = ft_strsub(line->buffer, i + 2, len);
	while (((char*)line->history->content)[++j])
	{
		line->buffer[i] = ((char *)line->history->content)[j];
		i++;
	}
	j = -1;
	while (tmp[++j])
		line->buffer[i++] = tmp[j];
	ft_strdel(&tmp);
}

void		check_expansions(t_read *line)
{
	int		i;

	i = -1;
	while (line->buffer[++i])
	{
		if (line->buffer[i] == '!')
		{
			if (line->buffer[i + 1] == '!')
				last_cmd_back(line, i);
			else if (ft_isdigit(line->buffer[i + 1]))
			{
				//expansion => "!number"
			}
			else if (is_print(line->buffer[i + 1]))
			{
				//expansion => "!word"
			}
			else if (line->buffer[i + 1] == '-' && ft_isdigit(line->buffer[i + 2]))
			{
				//expansion "!-number"
			}
		}
	}
}
