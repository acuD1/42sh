/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/17 19:08:49 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			display_subprompt(t_read *term)
{
	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->y = 0;
	term->width = term->x;
	term->x_index = term->x;
	ft_dprintf(STDERR_FILENO, term->prompt);
}

static u_int8_t	sub_prompt_error(t_read *term, char sb)
{
	if (term->flag == TRUE)
	{
		ft_dprintf(STDERR_FILENO,
			"42sh: unexpected EOF while looking for matching `%c'\n", sb);
		ft_dprintf(STDERR_FILENO,
							"42sh: syntax error: unexpected end of file\n");
		term->status = CMD_DONE;
		return (TRUE);
	}
	if (term->status != CMD_SUBPROMPT)
	{
		term->status = CMD_DONE;
		return (TRUE);
	}
	return (FALSE);
}

u_int8_t		read_multiline(t_read *term, char *sb)
{
	char	buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (check_caps(buff, term) == TRUE)
		{
			ft_bzero(buff, READ_SIZE);
			continue ;
		}
		else
		{
			if (term->status != CMD_SUBPROMPT)
				return (TRUE);
			if (!sb)
				return (FALSE);
			else if (*sb == BACKSLASH && check_backslash(term, sb) == FALSE)
				return (FALSE);
			else if (*sb != BACKSLASH && ft_strchr(term->buffer, *sb))
			{
				if (!check_backslash(term, sb))
					return (FALSE);
			}
			else if (*sb != BACKSLASH)
				term->buffer = ft_strjoinf(term->buffer, NEW_LINE, 1);
			break ;
		}
	}
	return (TRUE);
}

static u_int8_t	check_multi_subprompt(t_read *term, char *sb)
{
	if (*sb != BACKSLASH)
		term->buffer = ft_strjoinf(term->tmp_buff, term->buffer, 2);
	if (quotes_is_matching(term, sb) == FALSE)
	{
		if (*sb == BACKSLASH)
			term->buffer = ft_strjoinf(term->tmp_buff, term->buffer, 2);
		term->buffer = ft_strjoinf(term->buffer, NEW_LINE, 1);
		ft_strdel(&term->tmp_buff);
		term->tmp_buff = ft_strdup(term->buffer);
		return (TRUE);
	}
	else if (!*sb || *sb == BACKSLASH)
		term->buffer = ft_strjoinf(term->tmp_buff, term->buffer, 2);
	return (FALSE);
}

void			load_subprompt(char sb, t_read *term)
{
	if (sb != BACKSLASH)
		term->buffer = ft_strjoinf(term->buffer, NEW_LINE, 1);
	term->status = CMD_SUBPROMPT;
	term->tmp_buff = ft_strdup(term->buffer);
	term->flag = FALSE;
	while (TRUE)
	{
		ft_strdel(&term->buffer);
		term->buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(term);
		if (read_multiline(term, &sb) == FALSE)
		{
			if (check_multi_subprompt(term, &sb) == TRUE)
				continue ;
			else if (*term->prompt
				|| (!*term->prompt && term->buffer))
				break ;
		}
		if (sub_prompt_error(term, sb) == TRUE)
			return ;
		term->tmp_buff = ft_strjoinf(term->tmp_buff, term->buffer, 1);
	}
	ft_strdel(&term->tmp_buff);
	term->status = CMD_DONE;
}
