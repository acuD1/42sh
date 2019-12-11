/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_noi_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:30:48 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/12 00:45:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			load_noi_mode(t_core *shell)
{
	lexer_parser_analyzer(shell, shell->cmd_line.buffer);
	if (task_master(shell) != SUCCESS)
		exit(1);
	free_prompt(shell, shell->cmd_line.buffer);
	ft_strdel(&(shell->cmd_line.buffer));
}
