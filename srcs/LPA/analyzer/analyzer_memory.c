/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analyzer_memory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 20:31:06 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/16 17:17:26 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

static void	free_lpa(t_analyzer *anal)
{
	if (anal->redir.op[0])
		ft_strdel(&anal->redir.op[0]);
	if (anal->redir.op[1])
		ft_strdel(&anal->redir.op[1]);
	if (anal->redir.heredoc)
		ft_strdel(&anal->redir.heredoc);
	if (anal->redir_list)
		ft_free_redirlist(&anal->redir_list);
	if (anal->db.key)
		ft_strdel(&anal->db.key);
	if (anal->db.value)
		ft_strdel(&anal->db.value);
	if (anal->process.redir_list)
		ft_free_redirlist(&anal->process.redir_list);
	if (anal->process.assign_list)
		free_db(anal->process.assign_list);
	if (anal->process.command)
		ft_strdel(&anal->process.command);
	if (anal->process.tok_list)
		ft_freetokenlist(&anal->process.tok_list);
	if (anal->process_list)
		free_process_list(&anal->process_list);
}

t_analyzer	*exit_lpa(t_analyzer *anal, t_core *shell)
{
	shell->ctrl_c = 0;
	free_lpa(anal);
	if (anal->job.command)
		ft_strdel(&anal->job.command);
	if (anal->job.process_list)
		free_process_list(&anal->job.process_list);
	if (anal->job_list)
		ft_freejoblist(&anal->job_list);
	anal->state = A_STOP;
	anal->job_list = NULL;
	shell->status = 2;
	return (anal);
}

static void	ft_free_redir(t_redir *redir)
{
	ft_strdel(&(redir->op[0]));
	ft_strdel(&(redir->op[1]));
	ft_strdel(&(redir->heredoc));
	free(redir);
}

void		ft_free_redirlist(t_lst **head)
{
	t_lst	*ptr;
	t_lst	*next;

	if (head == NULL || *head == NULL)
		return ;
	ptr = *head;
	while (ptr)
	{
		next = ptr->next;
		ft_free_redir(ptr->content);
		free(ptr);
		ptr = next;
	}
}

void		free_process_list(t_lst **head)
{
	t_lst	*ptr;
	t_lst	*next;

	if (head == NULL || *head == NULL)
		return ;
	ptr = *head;
	*head = NULL;
	while (ptr != NULL)
	{
		next = ptr->next;
		ft_free_redirlist((t_lst **)&(((t_process *)ptr->content)->redir_list));
		free_db((((t_process *)ptr->content)->assign_list));
		ft_freetokenlist(&(((t_process *)ptr->content)->tok_list));
		ft_tabdel(&(((t_process *)ptr->content)->av));
		ft_tabdel(&(((t_process *)ptr->content)->envp));
		ft_strdel(&(((t_process *)ptr->content)->bin));
		ft_strdel(&(((t_process *)ptr->content)->command));
		free(ptr->content);
		free(ptr);
		ptr = next;
	}
}
