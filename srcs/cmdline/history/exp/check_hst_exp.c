/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hst_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:03:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/19 14:00:16 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

static char		*cmd_saved(t_read *term, ssize_t i)
{
	char	*tmp;
	ssize_t	j;

	tmp = NULL;
	j = 0;
	while (ft_isdigit(term->buffer[i++]))
		j++;
	tmp = ft_strdup(&term->buffer[j]);
	return (tmp);
}

static int8_t	check_valid_specifier(t_read *term, ssize_t i)
{
	while (term->buffer[i])
	{
		if (term->buffer[i - 1] == '-' && term->buffer[i] == '0')
		{
			ft_dprintf(STDERR_FILENO, "42sh: -0: event not found\n");
			return (FAILURE);
		}
		if (term->buffer[i] == '-' && ft_isdigit(term->buffer[i + 1]))
		{
			ft_dprintf(STDERR_FILENO, "42sh: -%c: bad word specifier\n",
				term->buffer[i + 1]);
			return (FAILURE);
		}
		i++;
	}
	return (SUCCESS);
}

static void		find_expansions(t_read *term, ssize_t i)
{
	char	*tmp;

	tmp = NULL;
	if (term->buffer[i + 1] == '!')
		i = last_cmd_back(term, i);
	else if (ft_isdigit(term->buffer[i + 1]))
	{
		tmp = cmd_saved(term, i);
		if ((i = call_number(term, i)) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: %s: event not found\n", tmp);
		ft_strdel(&tmp);
	}
	else if (ft_isalpha(term->buffer[i + 1]))
	{
		tmp = cmd_saved(term, i);
		if ((i = call_word(term, i)) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: %s: event not found\n", tmp);
		ft_strdel(&tmp);
	}
	else if (term->buffer[i + 1] == '-' && ft_isdigit(term->buffer[i + 2]))
	{
		if (check_valid_specifier(term, i + 2) == FAILURE)
		{
			i = -2;
			return ;
		}
		tmp = cmd_saved(term, i);
		if ((i = callback_number(term, i)) < 0)
			ft_dprintf(STDERR_FILENO, "42sh: %s: event not found\n", tmp);
		ft_strdel(&tmp);
	}
}

int8_t			check_expansions(t_read *term)
{
	char	*tmp;
	ssize_t	i;

	i = 0;
	if (ft_strequ(term->buffer, "!") == TRUE)
		return (FAILURE);
	tmp = ft_strdup(term->buffer);
	while (i < (ssize_t)ft_strlen(term->buffer) && term->buffer[i])
	{
		if (term->buffer[i] == '!')
			find_expansions(term, i);
		if (i < 0)
		{
			ft_strdel(&term->buffer);
			term->buffer = ft_memalloc(BUFF_SIZE + 1);
			ft_strdel(&tmp);
			return (FAILURE);
		}
		i++;
	}
	if (ft_strcmp(tmp, term->buffer))
		ft_dprintf(STDERR_FILENO, "%s\n", term->buffer);
	ft_strdel(&tmp);
	return (i == FAILURE ? FAILURE : SUCCESS);
}
