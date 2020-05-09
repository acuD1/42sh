/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ac_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 17:00:30 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/08 01:27:35 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static enum e_ac_type	get_file_type(char *input, size_t len)
{
	while (len > 0 && (input[len - 1] == ' ' || input[len - 1] == '\t'))
		len--;
	if (len == 0)
		return (AC_BINARY);
	return (AC_FILE);
}

static enum e_ac_type	get_type(char *input, size_t len)
{
	if (len == 0)
		return (AC_BINARY);
	if (input[len - 1] == ' ' || input[len - 1] == '\t' || input[len - 1] == '/'
		|| input[len - 1] == '>' || input[len - 1] == '<')
		return (get_file_type(input, len));
	if (input[len - 1] == '$')
		return (AC_VARIABLE);
	if (len > 1 && input[len - 1] == '{' && input[len - 2] == '$')
		return (AC_BRACKET);
	return (get_type(input, len - 1));
}

enum e_ac_type			ac_check_type(char *input)
{
	size_t		len;

	len = ft_strlen(input);
	if (len == 0)
		return (AC_BINARY);
	if (ft_strequ(".", input) == TRUE)
		return (AC_FILE);
	if (input[len - 1] == '$')
		return (AC_VARIABLE);
	return (get_type(input, len));
}
