/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printanalyze.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 13:55:13 by guvillat          #+#    #+#             */
/*   Updated: 2019/12/02 13:55:17 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			ft_printassignlist(t_lst *lst)
{
	t_lst		*assign;
	int			x;

	x = 0;
	if (!lst)
		return ;
	assign = lst;
	while (assign)
	{
		debug_ailleurs("/dev/ttys002", "============= ASSIGN ============\n");
		debug_ailleurs("/dev/ttys002", ((t_db*)assign->content)->key);
		debug_ailleurs("/dev/ttys002", ((t_db*)assign->content)->value);
		assign = assign->next;
		x++;
	}
}

void			ft_printredir(t_redir *redir)
{
	t_redir		*tmp;

	if (!redir)
		return ;
	tmp = redir;
	dprintf(nono("/dev/ttys002"), "redir state %u\n", tmp->type);
	if (tmp->op[0])
		dprintf(nono("/dev/ttys002"), "redir op[0] %s\n", tmp->op[0]);
	if (tmp->op[1])
		dprintf(nono("/dev/ttys002"), "redir op[1] %s\n", tmp->op[1]);
}

void			ft_printprocess(t_process *process)
{
	t_process	*tmp;
	t_token 	*tok;
	t_lst 		*ttp;

	if (!process)
		return ;
	tmp = process;
	dprintf(nono("/dev/ttys002"), "process state %u\n", tmp->type);
	if (tmp->av)
		ft_printtab(tmp->av);
	if (tmp->tok_list)
	{
		ttp = tmp->tok_list; 
		while (ttp)
		{
			tok = ttp->content;
			dprintf(nono("/dev/ttys002"), "data /%s/ id %u \n", tok->data ,tok->id);
			ttp = ttp->next;
		}
	}
}

void			ft_printjob(t_job *job)
{
	t_job		*tmp;

	if (!job)
		return ;
	tmp = job;
	dprintf(nono("/dev/ttys002"), "job state %u\n", tmp->type);
	// if (tmp->command)
		// dprintf(nono("/dev/ttys002"), "job command [%s]\n", tmp->command);
}

void			ft_printjoblst(t_lst *list)
{
	t_lst		*job;
	t_lst		*process;
	t_lst		*redir;

	if (!list)
		return ;
	job = list;
	while (job)
	{
		ft_printjob((t_job*)job->content);
		process = ((t_job*)job->content)->process_list;
		while (process)
		{
			ft_printprocess((t_process*)process->content);
			redir = ((t_process*)process->content)->redir_list;
			while (redir)
			{
				ft_printredir((t_redir*)redir->content);
				redir = redir->next;
			}
			ft_printassignlist(((t_process*)process->content)->assign_list);
			process = process->next;
		}
		job = job->next;
	}
	dprintf(nono("/dev/ttys002"), "\n");
}
