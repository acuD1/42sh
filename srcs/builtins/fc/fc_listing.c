/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_listing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:11:54 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/26 21:11:08 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		get_entries(t_lst *w, t_cmd *cmd)
{
	int			w_entries;

	w_entries = ft_lstlen(w);
	if (cmd->first <= 0)
		cmd->first = w_entries + cmd->first + 1;
	if (cmd->last <= 0)
		cmd->last = w_entries + cmd->last + 1;
	if (cmd->ac == 3)
		cmd->last = w_entries;
	if (cmd->ac == 2)
	{
		cmd->first = w_entries - 15;
		cmd->last = w_entries;
	}
}

void			swap(int *nb1, int *nb2)
{
	int			tmp;

	tmp = *nb1;
	*nb1 = *nb2;
	*nb2 = tmp;
}

static void		print_reverse(t_lst *w, t_cmd cmd)
{
	int			i;

	i = ft_lstlen(w);
	while (w && i >= cmd.first)
	{
		if (i <= cmd.last)
			ft_dprintf(cmd.fd, "%d\t%s\n", i, w->content);
		w = w->next;
		i--;
	}
}

static void		print_list(t_lst *w, t_cmd cmd)
{
	int			i;

	i = 1;
	while (w->next)
		w = w->next;
	while (w && i <= cmd.last)
	{
		if (i >= cmd.first)
			ft_dprintf(cmd.fd, "%d\t%s\n", i, w->content);
		w = w->prev;
		i++;
	}
}

u_int8_t		get_range(char **av, t_cmd *cmd)
{
	int		i;

	i = 0;
	while (*av && av[++i])
	{
		if (isstart(av[i], "-l") || isstart(av[i], "-r")
				|| isstart(av[i], "-n") || isstart(av[i], "-s")
				|| isstart(av[i], "-e"))
			continue ;
		else if (ft_isnum(av[i]) == FALSE)
			return (FALSE);
		else
		{
			cmd->first = ft_atoi(av[i]);
			break ;
		}
	}
	cmd->av = ft_memalloc(sizeof(char**));
	cmd->av[0] = av[i];
	cmd->av[1] = av[i + 1];
	if (i < ft_tablen(av) - 1)
		cmd->last = ft_atoi(av[i + 1]);
	cmd->ac = ft_tablen(av);
	return (TRUE);
}

int8_t		listing_mode(t_lst *w, char **av, u_int64_t opt)
{
	t_cmd	cmd;
	int		w_entries;

	ft_bzero(&cmd, sizeof(t_cmd));
	w_entries = ft_lstlen(w);
	if (get_range(av, &cmd) == FALSE)
		return (fc_error(opt, 0));
	cmd.fd = STDOUT_FILENO;
	get_entries(w, &cmd);
	if (cmd.last < cmd.first)
	{
		if (cmd.first > w_entries)
			cmd.first = w_entries;
		if (cmd.last > w_entries)
			cmd.last = w_entries;
		opt |= (1ULL << 17);
		swap(&cmd.first, &cmd.last);
	}
	if (opt & (1ULL << 17))
		print_reverse(w, cmd);
	else
		print_list(w, cmd);
	return (TRUE);
}
