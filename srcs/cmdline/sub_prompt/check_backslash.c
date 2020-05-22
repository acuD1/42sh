/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_backslash.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 15:44:01 by fcatusse          #+#    #+#             */
/*   Updated: 2020/03/12 15:28:27 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

u_int8_t	charset_count(t_read *term, char c, size_t i)
{
	u_int8_t	count;

	count = 0;
	while (term->buffer[i])
	{
		if (term->buffer[i] == c)
			count++;
		else if (c == BACKSLASH && count > 0 && term->buffer[i] != c)
			count = 0;
		i++;
	}
	return (count);
}

u_int8_t	check_backslash(t_read *term, char *quote)
{
	if (!*term->buffer)
		return (FALSE);
	if (term->buffer[ft_strlen(term->buffer) - 1] == BACKSLASH)
	{
		if (charset_count(term, BACKSLASH, 0) % 2 != 0)
		{
			*quote = BACKSLASH;
			return (TRUE);
		}
	}
	return (FALSE);
}

enum e_subp	backslash_subprompt(t_core *shell, t_subprompt *sub)
{
	if (check_backslash_nbr((char*)shell->term.buffer, &sub->index))
		sub->escaped = 1;
	sub->state = SP_START;
	return (sub->state);
}

void		del_keys_subprompt_and_move(t_subprompt *sub, char quote)
{
	sub->keys = del_keys_subprompt(quote, sub->keys);
	sub->index++;
}

void		reboot_or_end_machine(t_core *shell, t_subprompt *sub)
{
	if (sub->escaped)
	{
		open_machine_subprompt(shell, sub);
		sub->escaped = 0;
	}
	else if (sub->keys != NULL)
		open_machine_subprompt(shell, sub);
	else
		sub->state = SP_END;
}
