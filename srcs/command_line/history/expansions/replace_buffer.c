/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_buffer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 04:02:43 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/13 12:18:37 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		replace_buffer(t_read *term, char *begin, char *end, char *content)
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

}

/*
**		To insert in buffer the content found from the hst lst
*/

void			insert_content(int j, int i, t_read *term, char *content)
{
	char		*begin;
	char		*end;
	int			inc_len;

	inc_len = 0;
	end = NULL;
	begin = NULL;
	if (i >= BUFF_SIZE)
	{
		inc_len = ft_strlen(term->buffer) + ft_strlen((char *)content);
		term->buffer = realloc(term->buffer, inc_len);
	}
	if (i > 0)
		begin = ft_strsub(term->buffer, 0, i);
	if (i + 1 < (int)ft_strlen(term->buffer))
		end = ft_strsub(term->buffer, i + j, term->width - term->prompt_len);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE);
	replace_buffer(term, begin, end, content);
}
