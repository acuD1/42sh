/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_noi_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:30:48 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/24 15:54:35 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			load_noi_mode(t_core *shell)
{
	lexer_parser_analyzer(shell, shell->buff);
	if (task_master(shell) != SUCCESS)
		exit(1);
	free_prompt(shell, shell->buff);
	ft_strdel(&shell->buff);
}
