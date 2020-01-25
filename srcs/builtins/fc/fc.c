/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:30:58 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/25 18:41:13 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			get_range(char **cmd, char **range)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
//	ft_bzero(range, sizeof(range));
//	ft_bzero(range[1], sizeof(range[1]));
	while (j < 2 && cmd && cmd[++i])
	{
		if (isstart(cmd[i], "-l") || isstart(cmd[i], "-r")
				|| isstart(cmd[i], "-n") || isstart(cmd[i], "-s")
				|| isstart(cmd[i], "-e"))
			continue ;
		else
			range[++j] = cmd[i];
	}
	if (j == 2)
		j--;
	range[j + 1] = 0;
}

/*
**	Fix Command builtin have 2 modes :
**		Editing (default) & Listing (-lnr options)
*/

int8_t			builtin_fc(t_core *shell, t_process *process)
{
	t_lst		*saved;
	char		**cmd;
	char		*range[2];
	u_int64_t	opt;

	(void)process;
	if ((saved = shell->term.history) == NULL)
	{
		ft_dprintf(2, "42sh: fc: history specification out of range\n");
		return (FAILURE);
	}
	cmd = ft_strsplit(shell->term.buffer, SPACE);
	opt = get_options(ft_tablen(cmd), cmd, "elnrs0123456789");
	get_range(cmd, range);
	if (opt & (1ULL << 63))
	{
		print_usage("fc", opt % 128, "fc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]");
		return (FAILURE);
	}
	else if (saved && (opt & (1ULL << 18)))
		return (select_specifier(shell, saved, range));
	else if (saved && (opt & (1ULL << 11)))
		listing_mode(saved, opt, range);
	else
		edit_mode(shell, saved, opt, range);
	ft_tabdel(&cmd);
	return (SUCCESS);
}
