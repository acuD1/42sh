/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 14:02:13 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/18 20:18:29 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void		print_and_exec(t_core *shell, int fd)
{
	ft_dprintf(fd, "%s\n", shell->term.buffer);
	lexer_parser_analyzer(shell);
	do_job_notification(shell, shell->launched_jobs, TRUE);
	task_master(shell);
}

int32_t		search_pattern(char *pat, int8_t i)
{
	t_core	*shell;
	t_lst	*w;

	shell = get_core(NULL);
	w = shell->term.history;
	while (w)
	{
		if (i == 0 && ft_isstart(w->content, pat))
			return ((int32_t)w->content_size);
		else if (i == 1 && ft_strstr(w->content, pat) != NULL)
			return ((int32_t)w->content_size);
		w = w->next;
	}
	return (FAILURE);
}

int32_t		check_pattern(char *pat)
{
	int32_t		digit;

	if ((digit = search_pattern(pat, 0)) == FAILURE)
	{
		if ((digit = search_pattern(pat, 1)) == FAILURE)
		{
			return (FAILURE);
		}
	}
	return (digit);
}
