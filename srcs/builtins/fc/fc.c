/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:30:58 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/26 21:12:42 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t			fc_error(u_int64_t opt, int err_num)
{
	if (err_num == 0)
		ft_dprintf(2, "42sh: fc: history specification out of range\n");
	else if (err_num == 1)
		print_usage("fc", opt % 128, "fc: usage: fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]");
	else
		ft_dprintf(STDERR_FILENO,
				"42sh: fc: failed to open or create file: %s\n", "./.fc_file");
	return (FAILURE);
}

/*
**	Fix Command builtin have 2 modes :
**		Editing (default) & Listing (-lnr options)
*/

int8_t			builtin_fc(t_core *shell, t_process *process)
{
	t_lst		*w;
	u_int64_t	opt;

	opt = 0;
	if ((w = shell->term.history) == NULL)
		return (fc_error(opt, 0));
	opt = get_options(ft_tablen(process->av), process->av, "elnrs0123456789");
	if (opt & (1ULL << 63))
		return (fc_error(opt, 1));
	 else if (w && (opt & (1ULL << 18)))
	 	return (select_specifier(shell, w, process->av));
	else if (w && (opt & (1ULL << 11)))
		listing_mode(w, process->av, opt);
	/* else */
	/* 	edit_mode(shell, w, cmd, opt); */
	return (SUCCESS);
}
