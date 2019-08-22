/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:06:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/22 14:36:35 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**	Delete the last cmd in buffer if an another key tab is pressed
**	Termcaps `ce' => clear from the cursor to the end of the current line
*/

void			delete_last_cmd(char *d_name, t_read *input)
{
	int		i;
	int		buff_index;

	i = ft_strlen(d_name);
	buff_index = input->x_index - input->prompt_len - 1;
	while (i--)
	{
		input->buffer[buff_index] = '\0';
		move_left(d_name, input);
		buff_index--;
	}
	tputs(tgetstr("ce", NULL), 1, my_outc);
}

uint8_t			split_cmd(char **last_buf, char **to_find, t_read *input)
{
	if ((ft_strlen(input->buffer) == 0))
		return (FALSE);
	input->cmd = ft_split(input->buffer);
	input->ac = ft_tablen(input->cmd);
	*last_buf = input->cmd[ft_tablen(input->cmd) - 1];
	if (*last_buf)
		*to_find = ft_strdup(*last_buf);
	else
		return (FALSE);
	return (TRUE);
}

/*
**	Three auto_complete mode
**	- complete bin for the first argument only
**	- display all files of current dir
**	- complete char inserted with matching file
*/

void			auto_complete_mode(char *buf, t_read *input)
{
	char		*last_buf;
	char		*to_find;

	last_buf = NULL;
	to_find = NULL;
	input->found = 0;
	if (split_cmd(&last_buf, &to_find, input) == FALSE)
		return ;
	if (input->buffer[ft_strlen(input->buffer) - 1] == ' '
		|| (input->ac > 1 && !ft_strcmp(last_buf, "./")))
		display_current_directory(buf, input);
	else if (input->ac > 1)
		to_complete_buffer(buf, last_buf, to_find, input);
	else if (input->ac == 1)
	{
		if (!ft_strcmp(input->buffer, "./"))
			display_current_directory(buf, input);
		else
			walking_path_var(buf, to_find, input);
		if (input->found == 0)
			to_complete_buffer(buf, last_buf, to_find, input);
	}
	free(to_find);
	ft_tabfree(input->cmd);
}
