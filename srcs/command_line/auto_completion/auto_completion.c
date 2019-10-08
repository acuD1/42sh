/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:06:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/10/08 13:48:44 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/stat.h>

/*
**		Delete the last cmd in buffer if an another key tab is pressed
**		Termcaps `clr_end' => clear from the cursor to the end of the current line
*/

void			delete_last_cmd(char *d_name, t_read *input)
{
	int			i;
	int			buff_index;

	i = ft_strlen(d_name);
	buff_index = input->x_index - input->prompt_len - 1;
	while (i--)
	{
		input->buffer[buff_index] = '\0';
		move_left(d_name, input);
		buff_index--;
	}
	xtputs(input->termcaps->clr_end, 1, my_outc);
}

uint8_t			split_cmd(char **last_cmd, char **to_find, t_read *input)
{
	if ((ft_strlen(input->buffer) == 0))
		return (FALSE);
	input->cmd = ft_strsplit(input->buffer, " ");
	input->ac = ft_tablen(input->cmd);
	*last_cmd = input->cmd[ft_tablen(input->cmd) - 1];
	if (input->buffer[ft_strlen(input->buffer) - 1] == ' ')
		input->ac += 1;
	if (*last_cmd)
		*to_find = ft_strdup(*last_cmd);
	else
		return (FALSE);
	return (TRUE);
}


uint8_t			is_dir(char *dir)
{
	struct stat 	buf;

	if (lstat(dir, &buf) == FAILURE)
		return (FALSE);
	if (S_ISDIR(buf.st_mode))
		return (TRUE);
	return (FALSE);
}

/*
**		Four auto_complete mode
**		- complete bin for the first argument only
**		- display all files of current dir
**		- complete char inserted with matching file
**		- complete directories recursively
*/

void			auto_complete_mode(char *buf, t_read *input)
{
	char		*last_buf;
	char		*to_find;
	int			i;

	i = ft_strlen(input->buffer) - 1;
	last_buf = NULL;
	to_find = NULL;
	input->found = 0;
	if (split_cmd(&last_buf, &to_find, input) == FALSE)
		return ;
	if (input->ac > 1)
	{
		if (is_dir(to_find) || input->buffer[i] == ' ')
			display_current_directory(buf, input, to_find);
		else
			to_complete_buffer(last_buf, to_find, input);
	}
	else if (input->ac == 1)
	{
		if (is_dir(input->buffer) || isstart(input->buffer, "/"))
			read_directories(buf, to_find, input);
		else
			to_complete_bin(buf, to_find, input);
		if (input->found == 0)
			to_complete_buffer(last_buf, to_find, input);
	}
	free(to_find);
	ft_tabfree(input->cmd);
}
