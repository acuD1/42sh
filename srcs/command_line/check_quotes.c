/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:06:36 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/22 22:38:42 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		goto_next_quote(char *buffer, char quote_type, int *i)
{
	while (buffer[(*i)++] != '\0')
		if (buffer[*i] == quote_type)
			return (TRUE);
	return (FALSE);
}

char		set_quote_type(char quote)
{
	if (quote == QUOTE || quote == DQUOTE || quote == BQUOTE)
		return (quote);
	return ('\0');
}

uint8_t		quotes_is_matching(t_read *line)
{
	int	i;
	char	quote;

	i = -1;
	while (line->buffer[++i])
	{
		if ((quote = set_quote_type(line->buffer[i])) != '\0')
		{
			if (goto_next_quote(line->buffer, quote, &i) == TRUE)
				continue ;
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

uint8_t		check_quotes(t_read *line)
{
	int	i;
	char	quote;

	i = -1;
	if (quotes_is_matching(line) == TRUE)
		return (FALSE);
	if (ft_strchr(line->buffer, QUOTE)
			|| ft_strchr(line->buffer, DQUOTE))
	{
		while (line->buffer[++i])
			if ((quote = set_quote_type(line->buffer[i])) != '\0')
				break ;
		load_subprompt(quote, line);
		save_history(line);
		return (TRUE);
	}
	return (FALSE);
}
