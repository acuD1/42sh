/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:06:10 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/07 11:47:34 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**		Delete the last cmd in buffer if an another key tab is pressed
**		Termcaps `clr_end' => clear from the cursor to the end of the line
*/

void			delete_last_cmd(char *d_name, t_read *term)
{
	int			i;
	char		*tmp;

	tmp = NULL;
	i = term->width - term->prompt_len - ft_strlen(d_name);
	tmp = ft_strsub(term->buffer, 0, i);
	goto_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE);
	insert_str_in_buffer(tmp, term);
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

void			auto_complete_mode(t_read *term)
{
	char		*to_find;
	int			i;

	i = ft_strlen(term->buffer) - 1;
	to_find = NULL;
	if (split_cmd(&to_find, term) == FALSE)
		return ;
	if (term->ac > 1)
	{
		if (term->buffer[i] == ' ' || is_dir(to_find))
			display_current_directory(term, to_find);
		else
			to_complete_buffer(to_find, term);
	}
	else if (term->ac == 1)
	{
		if (is_dir(term->buffer) || isstart(term->buffer, "/"))
			read_directories(to_find, term);
		else if (ft_isalpha(*to_find))
			to_complete_bin(to_find, term);
		if (term->found == FALSE)
			to_complete_buffer(to_find, term);
	}
	ft_strdel(&to_find);
	ft_tabfree(term->cmd);
}
