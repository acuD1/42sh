/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subprompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:46:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/13 16:04:32 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t check_backslash_nbr(char *str, int *index)
{
	int i;
	int nbr;

	i = *index;
	nbr = 0;
	if (!str[i] || str[i] != BACKSLASH)
		return (0);
	if (str[i] == BACKSLASH)
	{
		while (str[i] == BACKSLASH)
		{
			i++;
			nbr++;
		}
	}
	if ((nbr % 2) == 1)
	{
		*index = i;
		return (1);
	}
	*index = i;
	return (0);
}

static u_int8_t	goto_next_quote(char *buffer, char quote_type, int *i)
{
	while (buffer[(*i)++] != '\0')
	{
		if (quote_type == '\"' && check_backslash_nbr(buffer, i))
			continue ;
		if (buffer[*i] == quote_type)
			return (TRUE);
	}
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
		load_subprompt(quote, &shell->term);
		return (TRUE);
	}
	return (FALSE);
}
