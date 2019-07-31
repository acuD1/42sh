/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   auto_completion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/23 13:06:10 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/31 12:16:42 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "twenty_one.h"

/*
** Delete the last cmd in buffer if an another key tab is pressed
** Termcaps `ce' clear from the cursor to the end of the current line
*/
void			delete_last_cmd(char *buf, char *d_name, t_read *input)
{
	int		i;
	int		buf_index;

	i = ft_strlen(d_name);
	buf_index = input->x_index - input->prompt_len;
	while (i--)
	{
		input->buffer[buf_index] = '\0';
		move_left(buf, input);
		buf_index--;
	}
	tputs(tgetstr("ce", NULL), 1, my_outc);
}

void			auto_complete_mode(char **env, char *buf, t_read *input)
{
	char		*last_buf;
	char		*to_find;

	input->cmd = ft_split(input->buffer);
	input->ac = ft_tablen(input->cmd);
	last_buf = input->cmd[ft_tablen(input->cmd) - 1];
	to_find = ft_strdup(last_buf);
	if (input->buffer[ft_strlen(input->buffer) - 1] == ' ')
		display_current_directory(buf, input);
	else if (input->ac > 1)
		to_complete_buffer(buf, last_buf, to_find, input);
	else if (input->ac == 1)
		walking_path_var(env, buf, input);
}
