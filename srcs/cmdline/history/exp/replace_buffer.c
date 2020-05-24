/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 04:02:43 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/24 17:49:15 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

ssize_t		check_exp_error(t_lst *w, ssize_t n)
{
	if (!w)
		return (FAILURE);
	if (n > (ssize_t)ft_lstlen(w) || n > get_history_value("HISTSIZE")
		|| n < 0)
		return (FAILURE);
	return (n);
}

static void	replace_buffer(t_read *term, char *begin, char *end, char *content)
{
	char	*tmp;

	tmp = NULL;
	if (term->width - term->prompt_len == 2)
		term->buffer = ft_strdup(content);
	else if (begin && end)
	{
		tmp = ft_strjoinf(begin, content, 1);
		term->buffer = ft_strjoinf(tmp, end, 3);
	}
	else if (end)
		term->buffer = ft_strjoinf(content, end, 2);
	else if (begin)
		term->buffer = ft_strjoinf(begin, content, 1);
	else
		term->buffer = ft_strdup(content);
}

/*
**		To insert in buffer the content found from the hst lst
*/

void		insert_content(ssize_t j, ssize_t i, t_read *term, char *content)
{
	char	*begin;
	char	*end;
	ssize_t	inc_len;
	ssize_t	buff_len;

	inc_len = 0;
	end = NULL;
	begin = NULL;
	buff_len = (ssize_t)ft_strlen(term->buffer);
	if (i >= BUFF_SIZE)
	{
		inc_len = (ssize_t)ft_strlen(term->buffer)
			+ (ssize_t)ft_strlen((char *)content);
		term->buffer = ft_realloc(term->buffer, (size_t)inc_len);
	}
	if (i > 0)
		begin = ft_strsub(term->buffer, 0, (size_t)i);
	if ((i + j) < buff_len)
		end = ft_strsub(term->buffer, (unsigned int)(i + j),
				(size_t)(buff_len - (i + j)));
	ft_strdel(&term->buffer);
	replace_buffer(term, begin, end, content);
}
