/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_hst_expansions.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 17:03:03 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/03 17:15:10 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

//Need remove ?
int8_t		debugu(const char *path, int i, char c)
{
	int fd;

	if ((fd = open(path, O_WRONLY)) < 0)
		return (-1);
	dprintf(fd, "i[%d] c{%c}\n", i, c);
	return (1);
}

static void	find_expansions(t_read *term, int *i)
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

void	check_expansions(t_read *term)
{
	int		i;
	int		buff_len;
	char	*tmp;

	i = -1;
	tmp = NULL;
	tmp = ft_strdup(term->buffer);
	buff_len = ft_strlen(term->buffer);
	while (buff_len--)
	{
		if (term->buffer[++i] == '!')
			find_expansions(term, &i);
	}
	if (ft_strcmp(tmp, term->buffer))
		ft_dprintf(STDOUT_FILENO, "%s\n", term->buffer);
	ft_strdel(&tmp);
}
