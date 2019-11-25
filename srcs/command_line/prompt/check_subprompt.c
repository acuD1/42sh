/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_subprompt.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:46:03 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/25 15:46:04 by fcatusse         ###   ########.fr       */
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

uint8_t		quotes_is_matching(t_read *line, char *quote)
{
	int	i;

	i = -1;
	while (line->buffer[++i])
	{
		if ((*quote = set_quote_type(line->buffer[i])) != '\0')
		{
			if (goto_next_quote(line->buffer, *quote, &i) == TRUE)
				continue ;
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

uint8_t		check_subprompt(t_read *input)
{
	int	i;
	char	quote;

	i = -1;
	quote = '\0';
	if (quotes_is_matching(input, &quote) == TRUE)
	{
		if (check_backslash(input, &quote) == FALSE)
			return (FALSE);
	}
	if (quote != '\0')
	{
		load_subprompt(quote, input);
		save_history(input);
		return (TRUE);
	}
	return (FALSE);
}
