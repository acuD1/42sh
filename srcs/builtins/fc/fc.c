/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 19:30:58 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/21 08:58:24 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

int8_t			fc_error(u_int64_t opt, int err_num)
{
	if (err_num == 0)
		ft_dprintf(STDERR_FILENO, FC_ERR1);
	else if (err_num == 1)
	{
		print_usage("fc", opt % 128,
			"fc [-e ename] [-lnr] [first] [last] or fc -s [pat=rep] [command]");
	}
	else if (err_num == 2)
	{
		ft_dprintf(STDERR_FILENO, FC_ERR2);
		ft_dprintf(STDERR_FILENO, "%s%s", FC_USAGE1, FC_USAGE2);
	}
	else if (err_num == 3)
		ft_dprintf(STDERR_FILENO, FC_ERR3);
	else
		ft_dprintf(STDERR_FILENO, "%s %s\n", FC_ERR_FILE, FC_TMP_FILE);
	return (FAILURE);
}

static int8_t	check_priority(char **av)
{
	size_t		i;
	size_t		j;

	i = ft_tablen(av) - 1;
	j = 0;
	while (av[i] && av[i][j])
		j++;
	if (av[i][j - 1] == 'e')
		return (FAILURE);
	return (SUCCESS);
}

/*
**	Fix Command builtin have 2 modes :
**	Editing (default) & Listing (-lnr options)
*/

int8_t			builtin_fc(t_core *shell, t_process *process)
{
	t_lst		*w;
	u_int64_t	opt;

	opt = 0;
	if ((w = shell->term.history) == NULL)
		return (fc_error(opt, 3));
	opt = ft_get_options((int)ft_tablen(process->av), process->av, FC_OPT);
	if (opt & (1ULL << 63))
		return (fc_error(opt, 1));
	if (opt & 1ULL << 4)
	{
		if (check_priority(process->av) == FAILURE)
			return (fc_error(opt, 2));
	}
	if (opt & (1ULL << 18))
		return (select_specifier(shell, process->av));
	else if (opt & (1ULL << 11))
		listing_mode(w, process->av, opt);
	else
		return (edit_mode(shell, process, opt));
	return (SUCCESS);
}
