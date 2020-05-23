/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_listing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 19:11:54 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/22 15:45:00 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

void		sort_print_cmd(t_cmd cmd, t_lst *w, u_int64_t opt)
{
	int32_t	w_entries;

	w_entries = (int32_t)ft_lstlen(w);
	if (cmd.last < cmd.first)
	{
		if (cmd.first < 0)
			cmd.first = 0;
		else if (cmd.first > w_entries)
			cmd.first = w_entries;
		if (cmd.last < 0)
			cmd.last = 0;
		else if (cmd.last > w_entries)
			cmd.last = w_entries;
		opt |= (1ULL << 17);
		ft_swap_int(&cmd.first, &cmd.last);
	}
	if (opt & (1ULL << 17))
		print_reverse(w, cmd, opt);
	else
		print_list(w, cmd, opt);
}

void		get_entries(t_lst *w, t_cmd *cmd, u_int64_t opt)
{
	int32_t		w_entries;

	w_entries = (int32_t)ft_lstlen(w);
	if (cmd->first > 0 && cmd->first > w_entries)
		cmd->first = w_entries;
	if (cmd->first < 0)
	{
		cmd->first++;
		if ((cmd->first * (-1)) > w_entries)
			cmd->first = 1;
	}
	if (cmd->first <= 0)
		cmd->first = w_entries + cmd->first;
	if (cmd->last <= 0)
		cmd->last = w_entries + cmd->last;
	if ((opt & (1ULL << 11)) && cmd->ac == 2)
	{
		cmd->first = w_entries - 15;
		cmd->last = w_entries;
	}
}

void		skip_options(char ***av)
{
	while (++(*av) && **av)
	{
		if (ft_isstart(**av, "-l") || ft_isstart(**av, "-r")
				|| ft_isstart(**av, "-n") || ft_isstart(**av, "-s")
				|| ft_isstart(**av, "-e") || ft_isstart(**av, "--"))
			continue ;
		else
			break ;
	}
	(*av)--;
}

int8_t		get_range(char **av, t_cmd *cmd, u_int64_t opt)
{
	if (*av == NULL)
		return (TRUE);
	skip_options(&av);
	if ((opt & (1ULL << 4) && opt & (1ULL << 17))
		|| opt & (1ULL << 4))
		av++;
	if (!(*(av + 1)) || !*av)
		return (TRUE);
	av++;
	if (*av && ft_isnum(*av) == FALSE)
	{
		if ((cmd->first = check_pattern(*av)) == FAILURE)
			return (FAILURE);
	}
	else if (*av)
		cmd->first = ft_atoi(*av);
	if (*(av + 1) && ft_isnum(*(av + 1)))
		cmd->last = ft_atoi(*(av + 1));
	else if (*(av + 1))
	{
		if ((cmd->last = check_pattern(*(av + 1))) == FAILURE)
			return (FAILURE);
	}
	return (TRUE);
}

int8_t		listing_mode(t_lst *w, char **av, u_int64_t opt)
{
	t_cmd		cmd;

	ft_bzero(&cmd, sizeof(t_cmd));
	cmd.ac = ft_tablen(av);
	if (cmd.ac != 2 && get_range(av, &cmd, opt) == FAILURE)
		return (fc_error(opt, 0));
	get_entries(w, &cmd, opt);
	cmd.fd = STDIN_FILENO;
	sort_print_cmd(cmd, w, opt);
	return (TRUE);
}
