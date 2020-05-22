/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:31:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:10 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		get_io_number(t_redir *ptr)
{
	ptr->io_num[0] = -1;
	ptr->io_num[1] = -1;
	ptr->dup_fd[0] = -1;
	ptr->dup_fd[1] = -1;
	ptr->close = -1;
	if (ptr->op[0] && ft_strcmp(ptr->op[0], "&") != 0)
		ptr->io_num[0] = ft_atoi(ptr->op[0]);
	else if (ptr->op[0])
	{
		ptr->io_num[0] = 1;
		ptr->io_num[1] = 2;
	}
}

static int8_t	get_fd(t_redir *redir)
{
	get_io_number(redir);
	if (!redir->op[1] || !*redir->op[1])
		return (FAILURE);
	if (redir->type == P_GREAT && redir_output(redir) != SUCCESS)
		return (FAILURE);
	if (redir->type == P_DGREAT && append_output(redir) != SUCCESS)
		return (FAILURE);
	if ((redir->type == P_LESS || redir->type == P_DLESS)
			&& redir_input(redir) != SUCCESS)
		return (FAILURE);
	if (redir->type == P_LESSAND && dup_ifd(redir) != SUCCESS)
		return (FAILURE);
	if (redir->type == P_GREATAND && dup_ofd(redir) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			exec_redirs(t_core *shell, t_process *process, t_lst *head)
{
	t_lst	*redirs;
	int8_t	i;

	i = 0;
	redirs = head;
	while (redirs != NULL)
	{
		if (((t_redir*)redirs->content)->type == P_DLESS)
			((t_redir*)redirs->content)->dup_fd[0] = shell->heredoc++;
		if (get_fd(((t_redir*)redirs->content)) != SUCCESS)
		{
			process->status = 1;
			process->completed = TRUE;
			return (FAILURE);
		}
		redirs = redirs->next;
	}
	return (SUCCESS);
}
