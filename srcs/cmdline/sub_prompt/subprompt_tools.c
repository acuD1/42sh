/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subprompt_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 17:11:13 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/08 14:43:41 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <unistd.h>

void			display_subprompt(t_read *term)
{
	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->y = 0;
	term->width = term->x;
	term->x_index = term->x;
	ft_dprintf(STDERR_FILENO, term->prompt);
}

u_int8_t		sub_prompt_error(t_read *term, char sb)
{
	if (term->flag == TRUE)
	{
		ft_dprintf(STDERR_FILENO,
			"42sh: unexpected EOF while looking for matching `%c'\n", sb);
		ft_dprintf(STDERR_FILENO,
							"42sh: syntax error: unexpected end of file\n");
		term->status = CMD_DONE;
		return (TRUE);
	}
	if (term->status != CMD_SUBPROMPT)
	{
		term->status = CMD_DONE;
		return (TRUE);
	}
	return (FALSE);
}
