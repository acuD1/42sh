/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_expansions.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:59:34 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/09 18:08:57 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**		To insert in buffer the content found from the hst lst
*/

int			insert_content(int j, int i, t_read *line, char *content)
{
	char		*tmp;
	int		len;

	if (i >= BUFF_SIZE)
		line->buffer = realloc(line->buffer, ft_strlen(line->buffer) + ft_strlen((char *)content));
	len = line->width - line->prompt_len - j;
	tmp = ft_strsub(line->buffer, i + j, len);
	j = -1;
	while (((char*)content)[++j])
	{
		line->buffer[i] = ((char *)content)[j];
		i++;
	}
	j = -1;
	len = i;
	while (tmp[++j])
		line->buffer[i++] = tmp[j];
	line->buffer[i] = 0;
	ft_strdel(&tmp);
	return (len - 1);
}

/*
**		"!word" expansion search the word to find from the end of hst lst
*/

void			call_word(t_read *line, int i)
{
	char		word[BUFF_SIZE];
	int		j;
	int		n;
	t_lst		*w;

	j = -1;
	w = line->history;
	n = i + 1;
	while (n < (int)ft_strlen(line->buffer) && !ft_isblank(line->buffer[n]))
	{
		word[++j] = line->buffer[n];
		n++;
	}
	word[j + 1] = '\0';
	if (!w || n > (int)ft_lstlen(w) || n > HIST_SIZE)
		return ;
	while (w->next)
	{
		if (isstart((char *)w->content, word))
			break ;
		w = w->next;
	}
	if (!w->next)
		return ;
	insert_content(j + 2, i, line, (char *)w->content);
}

/*
**		"!-number" expansion search from the end of hst lst
*/

void			callback_number(t_read *line, int i)
{
	char		nb[BUFF_SIZE];
	int		n;
	t_lst		*w;
	int		j;

	j = -1;
	w = line->history;
	n = i + 2;
	while (ft_isdigit(line->buffer[n]))
	{
		nb[++j] = line->buffer[n];
		n++;
	}
	n = ft_atoi(nb);
	if (!w || n > (int)ft_lstlen(w) || n > HIST_SIZE || n < 0)
		return ; // call error fct
	while (w && n != 0 && --n)
	{
		if (w->next)
			w = w->next;
	}
	insert_content(j + 3, i, line, (char *)w->content);
	i = i + j + 1;
}

/*
**		"!number" expansion search from the beggining of hst lst
*/

void			call_number(t_read *line, int i)
{
	char		nb[BUFF_SIZE];
	int		n;
	t_lst		*w;
	int		j;

	j = -1;
	w = line->history;
	n = i + 1;
	while (ft_isdigit(line->buffer[n]))
	{
		nb[++j] = line->buffer[n];
		n++;
	}
	n = ft_atoi(nb);
	if (!w || n > (int)ft_lstlen(w) || n > HIST_SIZE || n < 0)
		return ; //call error fct
	while (w->next)
		w = w->next;
	while (w && n != 0 && --n)
	{
		if (w->prev)
			w = w->prev;
	}
	insert_content(j + 2, i, line, (char *)w->content);
	i = i + j + 1;
}

/*
**		"!!" expansion search the last occurence of hst list
*/

void			last_cmd_back(t_read *line, int i)
{
	t_lst		*w;

	w = line->history;
	if (!line->history || ft_strlen(line->buffer) > BUFF_SIZE)
		return ;
	if (w && w->content)
		i = insert_content(2, i, line, (char *)w->content);
}
