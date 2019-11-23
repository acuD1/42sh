/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_noi_mode.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 11:30:48 by arsciand          #+#    #+#             */
/*   Updated: 2019/11/18 11:32:18 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			load_noi_mode(t_core *shell)
{
//	int8_t		status;
//	t_read		term;
//
//	status = 1;
//	credit(shell);
//	init_cmd_line(&term, shell);
/*	while (status)
	{*/
		//init_prompt(shell, &term);
		lexer_parser_analyzer(shell, shell->buff);
		if (task_master(shell) != SUCCESS)
			exit(1);
		free_prompt(shell, shell->buff);
		//break;
		//exit(24);
//	}
	//dprintf(STDERR_FILENO, "EXIT\n");
   //free_history(shell);
	//free(shell->history);
	ft_strdel(&shell->buff);
}
