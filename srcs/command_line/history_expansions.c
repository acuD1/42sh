/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:59:34 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/18 15:48:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		insert_content(int j, int i, t_read *line, char *content)
{
	char	*tmp;
	int		len;

	len = line->width - line->prompt_len - j;
	tmp = ft_strsub(line->buffer, i, len);
	while (i < BUFF_SIZE && ((char*)content)[++j])
	{
		line->buffer[i] = ((char *)content)[j];
		i++;
	}
	if (i >= BUFF_SIZE)
		return ;
	j = -1;
	while (tmp[++j])
		line->buffer[i++] = tmp[j];
	ft_strdel(&tmp);

}

void		callback_number(t_read *line, int i)
{
	char	nb[BUFF_SIZE];
	int		n;
	t_lst	*w;
	int		j;

	j = -1;
	w = line->history;
	while (ft_isdigit(line->buffer[i]))
	{
		nb[++j] = line->buffer[i];
		i++;
	}
	n = ft_atoi(nb);
	while (w && n != 0 && --n)
	{
		if (w->next)
			w = w->next;
	}
	insert_content(j, i, line, (char *)w->content);
}

void		last_cmd_back(t_read *line, int i)
{
	int		j;
	t_lst	*w;

	w = line->history;
	if (!line->history || ft_strlen(line->buffer) > BUFF_SIZE)
		return ;
	j = -1;
//	len = line->width - line->prompt_len - 2;
	insert_content(2, i + 2, line, (char *)w->content);
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
			if (ft_isdigit(line->buffer[i + 1]))
			{
				//expansion => "!number"
			}
			if (is_print(line->buffer[i + 1]))
			{
				//expansion => "!word"
			}
			if (line->buffer[i + 1] == '-' && ft_isdigit(line->buffer[i + 2]))
			{
				callback_number(line, i + 2);
				//expansion "!-number"
			}
		}
	}
}
