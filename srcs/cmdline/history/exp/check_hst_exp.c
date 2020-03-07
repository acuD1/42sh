/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hst_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:03:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/07 20:30:49 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	find_expansions(t_read *term, ssize_t *i)
{
	if (term->buffer[*i + 1] == '!')
		*i = last_cmd_back(term, *i);
	else if (ft_isdigit(term->buffer[*i + 1]))
		*i = call_number(term, *i);
	else if (ft_isalpha(term->buffer[*i + 1]))
		*i = call_word(term, *i);
	else if (term->buffer[*i + 1] == '-' && ft_isdigit(term->buffer[*i + 2]))
		*i = callback_number(term, *i);
}

int8_t		check_expansions(t_read *term)
{
	char	*tmp;
	ssize_t	i;

	i = 0;
	if (ft_strequ(term->buffer, "!") == TRUE)
		return (FAILURE);
	tmp = ft_strdup(term->buffer);
	while (term->buffer[i])
	{
		// C'est pas bon du tout, bcp de cas ou ca marche pas
		if (term->buffer[i] == '!')
			find_expansions(term, &i);
		if (i == FAILURE)
		{
			ft_dprintf(STDERR_FILENO, "42sh: %s: event not found\n", tmp);
			break ;
		}
		i++;
	}
	if (ft_strcmp(tmp, term->buffer))
		ft_dprintf(STDERR_FILENO, "%s\n", term->buffer);
	ft_strdel(&tmp);
	return (i == FAILURE ? FAILURE : SUCCESS);
}
