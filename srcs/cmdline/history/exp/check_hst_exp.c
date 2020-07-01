/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hst_exp.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:03:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/24 18:26:55 by fcatusse         ###   ########.fr       */
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

static int8_t	check_negative_specifier(t_read *term, ssize_t i)
{
	while (term->buffer[i] && term->buffer[i] != '!')
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

static int64_t	get_index(t_read *term, ssize_t i,
								int64_t (*fct)(t_read *, ssize_t))
{
	char		*tmp;

	tmp = NULL;
	if (term->buffer[i + 1] == '-')
	{
		if (check_negative_specifier(term, i + 2) == FAILURE)
		{
			i = -1;
			return (i);
		}
	}
	else if (term->buffer[i + 1] == '0')
	{
		ft_dprintf(STDERR_FILENO, "42sh: !0: event not found\n");
		return (FAILURE);
	}
	tmp = cmd_saved(term, i);
	if ((i = (*fct)(term, i)) < 0)
		ft_dprintf(STDERR_FILENO, "42sh: %s: event not found\n", tmp);
	ft_strdel(&tmp);
	return (i);
}

static void		find_expansions(t_read *term, ssize_t *i)
{
	if (term->buffer[*i + 1] == '!')
		*i = get_index(term, *i, &last_cmd_back);
	else if (ft_isdigit(term->buffer[*i + 1]))
		*i = get_index(term, *i, &call_number);
	else if (ft_isalpha(term->buffer[*i + 1]))
		*i = get_index(term, *i, &call_word);
	else if (term->buffer[*i + 1] == '-' && ft_isdigit(term->buffer[*i + 2]))
		*i = get_index(term, *i, &callback_number);
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
			find_expansions(term, &i);
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
