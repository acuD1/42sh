/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_keys.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:37:09 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/01 13:15:44 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		del_key(t_read *input)
{
	int		buf_index;
	char	*save;
	int		i;

	i = -1;
	if (input->x >= input->prompt_len * (input->y == 0 ? 1 : 0)
		&& input->x <= input->width)
	{
		buf_index = input->x_index - input->prompt_len;
		save = ft_strdup(input->buffer + buf_index + 1);
		ft_memset(input->buffer + buf_index,
			    0, ft_strlen(input->buffer + buf_index));
		tputs(tgetstr("dc", NULL), 1, my_outc);
		tputs(tgetstr("sc", NULL), 1, my_outc);
		while (save[++i])
		{
			ft_putchar(save[i]);
			input->buffer[buf_index++] = save[i];
		}
		input->buffer[buf_index + 1] = '\0';
		input->width--;
		tputs(tgetstr("rc", NULL), 1, my_outc);
		free(save);
	}
}

void		bs_key(char *buf, t_read *input)
{
	if ((input->y > 0 && input->x >= 0) || input->x > input->prompt_len)
	{
		move_left(buf, input);
		del_key(input);
	}
}
