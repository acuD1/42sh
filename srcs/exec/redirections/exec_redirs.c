/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:31:01 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/10 19:08:07 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	get_io_number(t_redir *ptr)
{
	ptr->io_num[0] = -1;
	ptr->io_num[1] = -1;
	if (ptr->op[0] && ft_strcmp(ptr->op[0], "&") != 0)
		ptr->io_num[0] = ft_atoi(ptr->op[0]);
	else if (ptr->op[0])
	{
		ptr->io_num[0] = 1;
		ptr->io_num[1] = 2;
	}
}

void			close_fds(t_lst *ptr)
{
	while (ptr)
	{
		if (((t_redir*)ptr->content)->dup_fd >= 0)
			close(((t_redir*)ptr->content)->dup_fd);
		ptr = ptr->next;
	}
}

static int8_t	get_fd(t_redir *redir)
{
	get_io_number(redir);
	dprintf(STDERR_FILENO, "%i\n", redir->type);
	if (redir->type == P_GREAT && redir_output(redir) != SUCCESS)
		return (FAILURE);
	if (redir->type == P_DGREAT && append_output(redir) != SUCCESS)
		return (FAILURE);
	if (redir->type == P_LESS && redir_input(redir) != SUCCESS)
		return (FAILURE);
	if (redir->type == P_LESSAND && dup_ifd(redir) != SUCCESS)
		return (FAILURE);
	if (redir->type == P_GREATAND && dup_ofd(redir) != SUCCESS)
		return (FAILURE);
	return (SUCCESS);
}

int8_t			exec_redirs(t_lst *head)
{
	t_lst *redirs;
	int		i;

	i = 0;
	redirs = head;
	while (redirs != NULL)
	{
		if (get_fd(((t_redir*)redirs->content)) != SUCCESS)
			exit(1);
		redirs = redirs->next;
	}
	return (SUCCESS);
}
