/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 16:22:02 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/08 18:36:25 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static char		*parse_variable(char *input, ssize_t len)
{
	while (len > 0)
	{
		if (input[len] == '$')
			return (input + len + 1);
		len--;
	}
	return (input + 1);
}

static char		*parse_file(char *input, ssize_t len)
{
	if (!ft_strchr(input, ' '))
		return (input);
	while (len > 0)
	{
		if (input[len] == ' ' || input[len] == '\t'
			|| input[len] == '}'
			|| input[len] == '>' || input[len] == '<')
			return (input + len + 1);
		len--;
	}
	if (input[0] == '/' || input[0] == '.' || input[0] == '~')
		return (input);
	return (input + 1);
}

static char		*parse_binary(char *input, ssize_t len)
{
	while (len > 0)
	{
		if (input[len] == '|' || input[len] == '&' || input[len] == ';')
			return (input + len + 1);
		len--;
	}
	return (input);
}

char			*ac_parse_input(char *input, enum e_ac_type type)
{
	ssize_t		input_len;

	input_len = (ssize_t)ft_strlen(input);
	if (type == AC_BINARY)
		return (parse_binary(input, input_len));
	if (type == AC_FILE)
		return (parse_file(input, input_len));
	if (type == AC_VARIABLE)
		return (parse_variable(input, input_len));
	if (type == AC_BRACKET)
		return (parse_variable(input, input_len) + 1);
	return (NULL);
}
