/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:06:02 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/29 20:05:51 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		print_reverse(t_lst *w, t_cmd cmd, u_int64_t opt)
{
	int			i;

	i = ft_lstlen(w);
	while (w && i >= cmd.first)
	{
		if ((i <= cmd.last && (opt & (1ULL << 13))))
			ft_dprintf(cmd.fd, "\t%s\n", w->content);
		else if (i <= cmd.last)
			ft_dprintf(cmd.fd, "%d\t%s\n", i, w->content);
		w = w->next;
		i--;
	}
}

void		print_list(t_lst *w, t_cmd cmd, u_int64_t opt)
{
	int			i;

	i = 1;
	while (w->next)
		w = w->next;
	while (w && i <= cmd.last)
	{
		if ((i >= cmd.first && (opt & (1ULL << 13))))
			ft_dprintf(cmd.fd, "\t%s\n", w->content);
		else if (i >= cmd.first)
			ft_dprintf(cmd.fd, "%d\t%s\n", i, w->content);
		w = w->prev;
		i++;
	}
}
