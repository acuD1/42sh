/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 21:58:29 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/24 18:40:30 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

uint8_t		heredoc_error(char *key)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: warning: here-document delimited by eof (wanted `%s')\n", key);
	return (FALSE);
}

int8_t		check_hc_reader(t_core *shell, char *key)
{
	if (read_multiline(&shell->term, FALSE) == FALSE)
	{
		if (shell->term.flag == TRUE)
			return (heredoc_error(key));
		if (ft_strcmp(shell->term.buffer, key))
		{
			shell->term.buffer = ft_strjoinf(shell->term.tmp_buff,
														shell->term.buffer, 2);
			shell->term.buffer = ft_strjoinf(shell->term.buffer, "\n", 1);
			ft_strdel(&shell->term.tmp_buff);
			shell->term.tmp_buff = ft_strdup(shell->term.buffer);
			return (TRUE);
		}
		else
			return (FALSE);
	}
	return (TRUE);
}

char		*stock_value(t_core *shell, int i)
{
	char	*value;
	char	*buffer;

	value = NULL;
	buffer = ft_strdup(shell->term.buffer);
	shell->term.tmp_buff = ft_strjoinf(shell->term.tmp_buff, buffer, 3);
	buffer = ft_strdup(shell->term.tmp_buff);
	shell->term.status = CMD_DONE;
	value = ft_strsub(buffer, i, ft_strlen(buffer));
	ft_strdel(&shell->term.buffer);
	shell->term.buffer = ft_strdup(buffer);
	ft_strdel(&buffer);
	reset_config(shell);
	return (value);
}

char		*load_heredoc(t_core *shell, char *key)
{
	char	*value;
	int		i;

	value = NULL;
	i = ft_strlen(shell->term.buffer) + 1;
	init_config(shell);
	shell->term.buffer = ft_strjoinf(shell->term.buffer, "\n", 1);
	shell->term.tmp_buff = ft_strdup(shell->term.buffer);
	shell->term.status = CMD_SUBPROMPT;
	while (TRUE)
	{
		ft_strdel(&shell->term.buffer);
		shell->term.buffer = ft_memalloc(BUFF_SIZE);
		display_subprompt(&shell->term, PS2);
		if (check_hc_reader(shell, key) == TRUE)
			continue ;
		else
			break ;
		if (shell->term.status == CMD_PROMPT)
			return (NULL);
	}
	value = stock_value(shell, i);
	return (value);
}
