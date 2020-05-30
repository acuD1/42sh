/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/27 15:06:02 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/30 18:57:14 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
**		Print history entries in fd open (STDIN or /tmp/42sh_fc.tmp file)
**		Handle all options (listing, reverse, no number, and edit mode)
*/

void	print_reverse(t_lst *w, t_cmd cmd, u_int64_t opt)
{
	int32_t	i;

	i = (int32_t)ft_lstlen(w);
	while (w && i >= cmd.first)
	{
		if ((i <= cmd.last && (opt & (1ULL << 13))))
			ft_dprintf(cmd.fd, "\t%s\n", w->content);
		else if (i <= cmd.last && (opt & (1ULL << 11)))
			ft_dprintf(cmd.fd, "%d\t%s\n", i, w->content);
		else if ((i <= cmd.last))
			ft_dprintf(cmd.fd, "%s\n", w->content);
		w = w->next;
		i--;
	}
}

void	print_list(t_lst *w, t_cmd cmd, u_int64_t opt)
{
	int32_t	i;

	i = 1;
	while (w->next)
		w = w->next;
	while (w && i <= cmd.last)
	{
		if ((i >= cmd.first && (opt & (1ULL << 13))))
			ft_dprintf(cmd.fd, "\t%s\n", w->content);
		else if (i >= cmd.first && (opt & (1ULL << 11)))
			ft_dprintf(cmd.fd, "%d\t%s\n", i, w->content);
		else if (i >= cmd.first)
			ft_dprintf(cmd.fd, "%s\n", w->content);
		w = w->prev;
		i++;
	}
}

void	print_and_exec(t_core *shell, int fd)
{
	ft_dprintf(fd, "%s\n", shell->term.buffer);
	lexer_parser_analyzer(shell);
	do_job_notification(shell, shell->launched_jobs, TRUE);
	task_master(shell);
}
