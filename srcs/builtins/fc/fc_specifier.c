/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_specifier.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:05:56 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/08 20:23:17 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char		*get_entry(t_lst *w, t_cmd cmd)
{
	int			i;

	i = ft_lstlen(w);
	if (cmd.ac == 2)
		cmd.first = i;
	else if (cmd.first > i)
		cmd.first = i;
	else if (cmd.first < -i)
		cmd.first = i;
	while (w && i >= cmd.first)
	{
		if (i == cmd.first)
		{
			ft_dprintf(cmd.fd, "%s\n", w->content);
			return (w->content);
		}
		w = w->next;
		i--;
	}
	return (NULL);
}

/*
**	[fc -s [old=new] [specifier]]
**		=> select specifier in history to re-enter
**		=> if new is specified history lst and file will b edit
*/

int8_t		select_specifier(t_core *shell, t_lst *w, char **av)
{
	t_cmd	cmd;
	char	*pat;
	char	*rep;

	pat = NULL;
	rep = NULL;
	if (get_range(av, &cmd) == FALSE)
		return (fc_error(0, 0));
	cmd.fd = STDOUT_FILENO;
	get_entries(w, &cmd);
	ft_strdel(&shell->term.buffer);
	if ((shell->term.buffer = ft_strdup(get_entry(w, cmd))) == NULL)
		return (fc_error(0, 0));
	return (SUCCESS);
}
