/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:29:40 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/12/15 03:50:46 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	dup_output(int fd, t_redir *ptr)
{
	int		tmp;

	tmp = dup2(fd, ptr->io_num[0]);
	ptr->dup_fd = 0;
	if (ptr->io_num[1] != -1 && tmp > 0)
	{
		ptr->dup_fd = dup2(tmp, ptr->io_num[1]);
		close(tmp);
	}
	close (fd);
	if (tmp < 0 || ptr->dup_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}

void	close_fds(t_lst *ptr)
{
	while (ptr)
	{
		if (((t_redir*)ptr->content)->dup_fd >= 0)
			close(((t_redir*)ptr->content)->dup_fd);
		ptr = ptr->next;
	}
}

int8_t	dup_input(int fd, t_redir *ptr)
{
	ptr->dup_fd = dup2(fd, ptr->io_num[0]);
	close(fd);
//	if (ptr->dup_fd < 0) HEREDOCS TEST
//		return (FAILURE);
	return (SUCCESS);
}
