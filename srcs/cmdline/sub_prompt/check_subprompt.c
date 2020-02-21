/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subprompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:46:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/21 16:30:26 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/* #include <fcntl.h> */
/* void			dbug(const char *path, char *buffer, char quote) */
/* { */
/* 	int			fd; */
/*  */
/* 	if ((fd = open(path, O_WRONLY)) == FAILURE) */
/* 		return ; */
/* 	dprintf(fd, "buff=[%s] buff[i]=[%c] quote=[%c]\n\n", buffer, *buffer, quote); */
/* } */

static u_int8_t	goto_next_quote(char *buffer, char quote_type, int *i)
{
	while (buffer[(*i)++] != '\0')
		if (buffer[*i] == quote_type)
			return (TRUE);
	return (FALSE);
}

static char		set_quote_type(char quote)
{
	if (quote == QUOTE || quote == DQUOTE || quote == BQUOTE)
		return (quote);
	else if (quote == BRACKET_OPEN)
		return (quote = BRACKET_CLOSE);
	else if (quote == CURLY_BRACKET_OPEN)
		return (quote = CURLY_BRACKET_CLOSE);
	return ('\0');
}

u_int8_t		quotes_is_matching(t_read *term, char *quote)
{
	int			i;

	i = -1;
	term->flag = FALSE;
	while (term->buffer[++i])
	{
		if (term->buffer[i + 1] == BACKSLASH
			&& ((*quote = set_quote_type(term->buffer[i])) != QUOTE))
		{
			if (term->buffer[i + 3] == '\0')
				return (FALSE);
			continue ;
		}
		if ((*quote = set_quote_type(term->buffer[i])) != '\0')
		{
			if (goto_next_quote(term->buffer, *quote, &i) == TRUE)
				continue ;
			else
				term->flag = TRUE;
		}
	}
	if (term->flag == TRUE)
		return (FALSE);
	return (TRUE);
}

u_int8_t		check_subprompt(t_core *shell)
{
	char		quote;

	quote = '\0';
	if (quotes_is_matching(&shell->term, &quote) == TRUE)
		if (check_backslash(&shell->term, &quote) == FALSE)
			return (FALSE);
	if (quote != '\0')
	{
		shell->term.sub_prompt = TRUE;
		ft_strdel(&shell->term.prompt);
		get_prompt_value(shell, "PS2");
		shell->term.status = CMD_SUBPROMPT;
		load_subprompt(quote, &shell->term);
		return (TRUE);
	}
	return (FALSE);
}
