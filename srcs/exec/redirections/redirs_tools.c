/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:29:40 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 16:56:16 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <fcntl.h>
#include <unistd.h>

int8_t	dup_output(int fd, t_redir *ptr)
{
	int		tmp;

	ptr->dup_fd[0] = dup(ptr->io_num[0]);
	tmp = dup2(fd, ptr->io_num[0]);
	ptr->close = fd;
	if (ptr->io_num[1] != -1 && tmp >= 0)
	{
		ptr->dup_fd[1] = dup(ptr->io_num[1]);
		dup2(tmp, ptr->io_num[1]);
		if (ptr->dup_fd[1] < 0)
			return (FAILURE);
	}
	if (tmp < 0)
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
		if (ptr->close >= 0)
			close(ptr->close);
	}
}

int8_t	dup_input(int fd, t_redir *ptr)
{
	int		tmp;

	ptr->dup_fd[0] = dup(ptr->io_num[0]);
	tmp = dup2(fd, ptr->io_num[0]);
	ptr->close = fd;
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
	ft_strdel(&(ptr->op[1]));
	ptr->op[1] = ft_strdup(filename);
	ft_putstr_fd(ptr->heredoc, fd);
	close(fd);
	return (SUCCESS);
}
