/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_noi_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:30:48 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/22 16:05:17 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			load_noi_mode(t_core *shell)
{
	lexer_parser_analyzer(shell);
	if (task_master(shell) != SUCCESS)
		exit(1);
	free_prompt(shell);
}
