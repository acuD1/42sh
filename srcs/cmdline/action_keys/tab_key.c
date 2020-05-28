/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tab_key.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 12:40:04 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/28 15:24:46 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		display_prompt_and_buffer(t_read *term)
{
	ssize_t		x_index;
	char		*buffer;

	x_index = term->x_index;
	buffer = ft_strdup(term->buffer);
	if (term->ctrl_c == FALSE)
		ft_putchar_fd('\n', STDERR_FILENO);
	if (term->status == CMD_SUBPROMPT)
		display_subprompt(term);
	else if (term->status == CMD_PROMPT && term->ctrl_c == FALSE)
		display_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	insert_str_in_buffer(buffer, term);
	while (term->x_index > x_index)
		move_left(term);
	ft_strdel(&buffer);
}

int8_t			tab_key(t_core *shell)
{
	char		*output;
	char		*str;

	output = NULL;
	shell->ac_flag = SUCCESS;
	str = ft_strdup(shell->term.buffer);
	if (str != NULL && shell->term.x_index < shell->term.width)
		str[shell->term.x_index - shell->term.prompt_len] = '\0';
	if (auto_complete_mode(str, shell, &output) == FAILURE)
	{
		ft_strdel(&str);
		return (FAILURE);
	}
	if (output != NULL)
	{
		insert_str_in_buffer(output, &shell->term);
		ft_strdel(&output);
	}
	else
		display_prompt_and_buffer(&shell->term);
	ft_strdel(&str);
	return (SUCCESS);
}
