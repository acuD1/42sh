/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_listing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:11:54 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/07 01:21:29 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		get_entries(t_lst *w, t_cmd *cmd)
{
	int		w_entries;

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

static void	swap(int *nb1, int *nb2)
{
	int		tmp;

	tmp = *nb1;
	*nb1 = *nb2;
	*nb2 = tmp;
}

void		skip_options(char ***av)
{
	while (++(*av) && **av)
	{
		if (ft_isstart(**av, "-l") || ft_isstart(**av, "-r")
				|| ft_isstart(**av, "-n") || ft_isstart(**av, "-s")
				|| ft_isstart(**av, "-e"))
			continue ;
		else
			break ;
	}
	(*av)--;
}

u_int8_t	get_range(char **av, t_cmd *cmd)
{
	int		i;

	i = 0;
	if ((cmd->ac = ft_tablen(av)) == 2)
		return (TRUE);
	skip_options(&av);
	if (ft_tabchr(av, "-e"))
		av++;
	while (*av && av++)
	{
		if (ft_isnum(*av) == FALSE)
			return (FALSE);
		else
		{
			cmd->first = ft_atoi(*av);
			break ;
		}
	}
	if (*(av + 1))
		cmd->last = ft_atoi(*(av + 1));
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
		print_reverse(w, cmd, opt);
	else
		print_list(w, cmd, opt);
	return (TRUE);
}
