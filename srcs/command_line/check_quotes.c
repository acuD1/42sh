/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:06:36 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/04 20:47:44 by fcatusse         ###   ########.fr       */
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
	if (quote == '\'' || quote == '\"')
		return (quote);
	return ('\0');
}

uint8_t		quotes_is_matching(t_read *line)
{
	int	i;
	char	quote_type;

	i = -1;
	while (line->buffer[++i])
	{
		if ((quote_type = set_quote_type(line->buffer[i])) != '\0')
		{
			if (goto_next_quote(line->buffer, quote_type, &i) == TRUE)
				continue ;
			else
				return (FALSE);
		}
	}
	return (TRUE);
}

void		remove_quotes(t_read *line)
{
	char	*tmp;
	int	i;
	int	j;

	i = -1;
	j = -1;
	tmp = ft_strdup(line->buffer);
	ft_bzero(line->buffer, line->width);
	while (tmp[++i])
	{
		if (tmp[i] == '\'' || tmp[i] == '\"')
			line->width--;
		else
			line->buffer[++j] = tmp[i];
	}
	ft_strdel(&tmp);
}

void		check_quotes(t_read *line)
{
	if (quotes_is_matching(line) == TRUE)
		remove_quotes(line);
	else if (ft_strchr(line->buffer, '\''))
		load_subshell_quote(line);
}
