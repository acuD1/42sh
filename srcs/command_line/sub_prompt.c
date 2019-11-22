/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/22 21:11:52 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		insert_newline_in_buff(t_read *input)
{
	int		buff_index;

	buff_index = input->x_index - input->prompt_len;
	input->buffer[buff_index] = NEW_LINE;
	input->width++;
	input->x = 0;
	input->y++;
	input->x_index++;
}

void		display_subprompt(t_read *term, char *prompt)
{
	term->prompt = ft_strdup(prompt);
	term->prompt_len = ft_strlen(term->prompt);
	term->x = term->prompt_len;
	term->y = 0;
	term->width = term->x;
	term->x_index = term->x;
	term->sub_prompt = 1;
	ft_printf(term->prompt);
}

uint8_t		read_subline(t_read *input, char quote)
{
	char	buff[READ_SIZE + 1];

	ft_bzero(buff, READ_SIZE);
	while (xread(STDIN_FILENO, buff, READ_SIZE) > 0)
	{
		if (check_caps(buff, input) == TRUE)
		{
			ft_bzero(buff, READ_SIZE);
			continue ;
		}
		else
		{
			if (ft_strchr(input->buffer, quote))
				return (FALSE);
			input->buffer[ft_strlen(input->buffer)] = NEW_LINE;
			break ;
		}
	}
	return (TRUE);
}

void		load_subprompt(char quote, t_read *input)
{
	insert_newline_in_buff(input);
	input->tmp_buff = ft_strdup(input->buffer);
	while (TRUE)
	{
		free(input->buffer);
		input->buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(input, PS2);
		if (read_subline(input, quote) == FALSE)
		{
			input->sub_prompt = FALSE;
			input->buffer = ft_strjoin(input->tmp_buff, input->buffer);
			break ;
		}
		input->tmp_buff = ft_strjoinf(input->tmp_buff, input->buffer, 1);
	}
}
