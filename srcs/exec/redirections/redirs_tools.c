/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:29:40 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/11/19 17:46:31 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t	dup_output(int fd, t_redir *ptr)
{
	int		tmp;

	tmp = dup2(fd, ptr->io_num[0]);
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

int8_t	dup_input(int fd, t_redir *ptr)
{
	ptr->dup_fd = dup2(fd, ptr->io_num[0]);
	close(fd);
	if (ptr->dup_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}
