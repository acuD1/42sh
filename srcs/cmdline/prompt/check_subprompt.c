/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subprompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:46:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/06 22:32:10 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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
	int		i;

	i = -1;
	while (term->buffer[++i])
	{
		if (term->buffer[i] == BACKSLASH)
		{
			i++;
			continue ;
		}
		if ((*quote = set_quote_type(term->buffer[i])) != '\0')
		{
			if (goto_next_quote(term->buffer, *quote, &i) == TRUE)
				continue ;
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

u_int8_t		check_subprompt(t_core *shell)
{
	int		i;
	char	quote;

	i = -1;
	quote = '\0';
	if (quotes_is_matching(&shell->term, &quote) == TRUE)
		if (check_backslash(&shell->term, &quote) == FALSE)
			return (FALSE);
	if (quote != '\0')
	{
		shell->term.sub_prompt = TRUE;
		ft_strdel(&shell->term.prompt);
		get_prompt_value(shell, "PS2");
		load_subprompt(quote, &shell->term);
		return (TRUE);
	}
	return (FALSE);
}
