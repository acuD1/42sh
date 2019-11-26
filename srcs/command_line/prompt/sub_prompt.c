/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_prompt.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/13 17:07:08 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/26 18:05:31 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		debug(char  *path, t_read *in, char c)
{
    int fd;

    if ((fd = open(path, O_WRONLY)) < 0)
        return (FAILURE);
    dprintf(fd, " bff[%s] tmp[%s]\n sb[%c]\n\n", in->buffer, in->tmp_buff, c);
    return (SUCCESS);
}

/* void		insert_newline_in_buff(t_read *input) */
/* { */
/* 	int		buff_index; */
/*  */
/* 	buff_index = input->x_index - input->prompt_len; */
/* 	input->buffer[buff_index] = NEW_LINE; */
/* 	input->width++; */
/* 	input->x = 0; */
/* 	input->y++; */
/* 	input->x_index++; */
/* } */

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

uint8_t		read_subline(t_read *input, char sb)
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
			if (sb == BACKSLASH && check_backslash(input, &sb) == FALSE)
				return (FALSE);
			else if (sb != BACKSLASH && ft_strchr(input->buffer, sb))
				return (FALSE);
			else if (sb != BACKSLASH)
				input->buffer[ft_strlen(input->buffer)] = NEW_LINE;
			break ;
		}
	}
	return (TRUE);
}

void		load_subprompt(char sb, t_read *input)
{
	if (sb != BACKSLASH)
		input->buffer[ft_strlen(input->buffer)] = NEW_LINE;
	input->tmp_buff = ft_strdup(input->buffer);
	while (TRUE)
	{
		free(input->buffer);
		input->buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(input, PS2);
		if (read_subline(input, sb) == FALSE)
		{
			input->sub_prompt = FALSE;
			input->buffer = ft_strjoin(input->tmp_buff, input->buffer);
			if (quotes_is_matching(input, &sb) == FALSE)
			{
				input->buffer[ft_strlen(input->buffer)] = NEW_LINE;
				debug("/dev/pts/2", input, sb);
				free(input->tmp_buff);
				input->tmp_buff = ft_strdup(input->buffer);
				continue ;
			}
			else
				break ;
		}
		input->tmp_buff = ft_strjoinf(input->tmp_buff, input->buffer, 1);
	}
	ft_strdel(&input->tmp_buff);
}
