/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:29:40 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/14 03:58:40 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "sh42.h"

int8_t	dup_output(int fd, t_redir *ptr)
{
	int		tmp;

	ptr->dup_fd[0] = dup(ptr->io_num[0]);
	tmp = dup2(fd, ptr->io_num[0]);
	if (ptr->io_num[1] != -1 && tmp >= 0)
	{
		ptr->dup_fd[1] = dup(ptr->io_num[1]);
		dup2(tmp, ptr->io_num[1]);
		close(tmp);
	}
	close(fd);
	if (tmp < 0 || ptr->dup_fd < 0)
		return (FAILURE);
	return (SUCCESS);
}

void	close_fds(t_lst *redirs)
{
	t_redir	*ptr;

	if (redirs)
	{
		close_fds(redirs->next);
		ptr = ((t_redir*)redirs->content);
		if (ptr->dup_fd[0] >= 0)
		{
			dup2(ptr->dup_fd[0], ptr->io_num[0]);
			close(ptr->dup_fd[0]);
		}
		if (ptr->dup_fd[1] >= 0)
		{
			dup2(ptr->dup_fd[1], ptr->io_num[1]);
			close(ptr->dup_fd[1]);
		}
	}
}

int8_t	dup_input(int fd, t_redir *ptr)
{
	int		tmp;

	ptr->dup_fd[0] = dup(ptr->io_num[0]);
	tmp = dup2(fd, ptr->io_num[0]);
	close(fd);
	if (tmp < 0)
		return (FAILURE);
	return (SUCCESS);
}

int8_t	write_heredoc(t_redir *ptr)
{
	char	filename[24];
	int		fd;

	ft_bzero(filename, 24);
	ft_strcat(filename, ".tmphdoc");
	if ((fd = open(filename, O_WRONLY | O_TRUNC | O_CREAT
					, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR)) < 0)
		return (FAILURE);
	ptr->op[1] = ft_strdup(filename);
	ft_putstr_fd(ptr->heredoc, fd);
	close(fd);
	return (SUCCESS);
}
