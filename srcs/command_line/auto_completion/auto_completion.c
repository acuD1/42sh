/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:06:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/10 19:17:07 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**		Delete the last cmd in buffer if an another key tab is pressed
**		Termcaps `clr_end' => clear from the cursor to the end of the current line
*/

void			delete_last_cmd(char *d_name, t_read *input)
{
	int			i;
	char		*tmp;

	tmp = NULL;
	i = input->width - input->prompt_len - ft_strlen(d_name);
	tmp = ft_strsub(input->buffer, 0, i);
	goto_prompt(input);
	ft_strdel(&input->buffer);
	input->buffer = ft_memalloc(BUFF_SIZE);
	insert_str_in_buffer(tmp, input);
	ft_strdel(&tmp);
}

uint8_t			is_dir(char *dir)
{
	struct stat	buf;

	if (!dir)
		return (FALSE);
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
		if (input->buffer[i] == ' ')
			display_current_directory(buf, input, to_find);
		else
			to_complete_buffer(last_buf, to_find, input);
	}
	else if (input->ac == 1)
	{
		if (is_dir(input->buffer) || isstart(input->buffer, "/"))
			read_directories(buf, to_find, input);
		else if (ft_isalpha(*to_find))
			to_complete_bin(buf, to_find, input);
		if (input->found == 0)
			to_complete_buffer(last_buf, to_find, input);
	}
	free(to_find);
	ft_tabfree(input->cmd);
}
