/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt_loader.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/12 16:55:33 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/06 11:03:23 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void	subprompt_loader(t_core *shell)
{
	while (TRUE && shell->term.status == CMD_SUBPROMPT)
	{
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE + 1);
		display_subprompt(&shell->term);
		if (read_multiline(shell) == FALSE)
			break ;
	}
}
