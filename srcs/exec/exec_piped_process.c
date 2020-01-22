/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 02:51:27 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/30 14:43:07 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int32_t	exec_piped_process(t_core *shell, t_lst *process)
{
	int		blt;

	expansion(shell, ((t_process*)process->content));
	if (((t_process*)process->content))
		if ((blt = is_a_blt(((t_process*)process->content)->av[0])) != FAILURE)
			exit(call_builtin(shell, process, blt));
	get_bin(shell, ((t_process*)process->content));
	call_bin(shell, process);
	exit(0);
}
