/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_piped_process.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 02:51:27 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/05 02:52:46 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int32_t	exec_piped_process(t_core *shell, t_lst *process)
{
	int		blt;

	//EXPANSION
	if ((blt = is_a_blt(((t_process*)process->content)->av[0])) != FAILURE)
		exit(call_builtin(shell, process, blt));
	call_bin(shell, process);
	exit(0);
}
