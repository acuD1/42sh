/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:06:10 by fcatusse          #+#    #+#             */
/*   Updated: 2020/04/17 11:50:32 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include "sh42.h"

/*
**		Delete the last cmd in buffer if an another key tab is pressed
**		Termcaps `clr_end' => clear from the cursor to the end of the line
*/

void		delete_last_cmd(const char *d_name, t_read *term)
{
	ssize_t	i;
	char	*tmp;

	tmp = NULL;
	i = term->width - (ssize_t)term->prompt_len - (ssize_t)ft_strlen(d_name);
	ft_strdel(&tmp);
	tmp = ft_strsub(term->buffer, 0, (size_t)i);
	goto_prompt(term);
	ft_strdel(&term->buffer);
	term->buffer = ft_memalloc(BUFF_SIZE + 1);
	insert_str_in_buffer(tmp, term);
	ft_strdel(&tmp);
}

u_int8_t	is_dir(const char *dir)
{
	struct stat	buf;
	char		*tmp;

	if (!*dir || !dir)
		return (FALSE);
	if (!ft_isstart(dir, "/"))
		tmp = ft_strjoin("./", dir);
	else
		tmp = ft_strdup(dir);
	if (lstat(dir, &buf) == FAILURE)
	{
		ft_strdel(&tmp);
		return (FALSE);
	}
	if (S_ISDIR(buf.st_mode) && !is_dot(dir))
	{
		ft_strdel(&tmp);
		return (TRUE);
	}
	ft_strdel(&tmp);
	return (FALSE);
}

/*
**		Four auto_complete mode
**		- complete bin for the first argument only
**		- display all files of current dir
**		- complete char inserted with matching file
**		- complete directories recursively
*/

void		auto_complete_mode(t_read *term)
{
	char	*to_find;
	ssize_t	i;

	i = term->x_index - term->prompt_len - 1;
	to_find = NULL;
	split_cmd(&to_find, term);
	if (term->ac > 1)
	{
		if (term->buffer[i] == ' ' || (is_dir(to_find)
			&& !is_dot(&to_find[ft_strlen(to_find) - 1])))
			display_current_directory(term, to_find);
		else
			to_complete_buffer(to_find, term);
	}
	else if (term->ac <= 1)
	{
		if (is_dir(term->buffer) || ft_isstart(term->buffer, "/"))
			read_directories(to_find, term);
		else if (!*term->buffer || ft_isalpha(*to_find))
			to_complete_bin(to_find, term);
		else if (term->flag == FALSE)
			to_complete_buffer(to_find, term);
	}
	ft_strdel(&to_find);
	ft_tabfree(term->cmd);
}
