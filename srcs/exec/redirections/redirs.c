/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 03:31:42 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/02/06 18:39:20 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include "sh42.h"

int8_t	append_output(t_redir *ptr)
{
	int	fd;

	if (ptr->io_num[0] < 0)
		ptr->io_num[0] = 1;
	if ((fd = open(ptr->op[1], O_WRONLY | O_APPEND | O_CREAT
				, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR)) < 0)
	{
		if (is_a_dir(ptr->op[1]) == EISDIR)
			ft_perror(ptr->op[1], NULL, EISDIR);
		else
			ft_perror(ptr->op[1], NULL, ft_access(ptr->op[1], W_OK));
		return (FAILURE);
	}
	return (dup_output(fd, ptr));
}

int8_t	redir_output(t_redir *ptr)
{
	int		fd;

	if (ptr->io_num[0] < 0)
		ptr->io_num[0] = 1;
	if ((fd = open(ptr->op[1], O_WRONLY | O_TRUNC | O_CREAT
				, S_IRUSR | S_IRGRP | S_IROTH | S_IWUSR)) < 0)
	{
		if (is_a_dir(ptr->op[1]) == EISDIR)
			ft_perror(ptr->op[1], NULL, EISDIR);
		else
			ft_perror(ptr->op[1], NULL, ft_access(ptr->op[1], W_OK));
		return (FAILURE);
	}
	return (dup_output(fd, ptr));
}

int8_t	redir_input(t_redir *ptr)
{
	int		fd;

	if (ptr->io_num[0] < 0)
		ptr->io_num[0] = 0;
	if (ptr->type == P_DLESS && write_heredoc(ptr) != SUCCESS)
		return (FAILURE);
	if ((fd = open(ptr->op[1], O_RDONLY)) < 0)
	{
		if (is_a_dir(ptr->op[1]) == EISDIR)
			ft_perror(ptr->op[1], NULL, EISDIR);
		else
			ft_perror(ptr->op[1], NULL, ft_access(ptr->op[1], R_OK));
		return (FAILURE);
	}
	if (ptr->type == P_DLESS)
		unlink(ptr->op[1]);
	return (dup_input(fd, ptr));
}

int8_t	dup_ifd(t_redir *ptr)
{
	if (ptr->io_num[0] < 0)
		ptr->io_num[0] = 0;
	if (ft_strcmp(ptr->op[1], "-") == 0)
	{
		ptr->dup_fd[0] = dup(ptr->io_num[0]);
		close(ptr->io_num[0]);
		return (SUCCESS);
	}
	ptr->dup_fd[0] = ft_atoi(ptr->op[1]);
	if ((ptr->dup_fd[0] = dup2(ptr->dup_fd[0], ptr->io_num[0])) < 0)
		return (FAILURE);
	return (SUCCESS);
}

int8_t	dup_ofd(t_redir *ptr)
{
	if (ptr->io_num[0] < 0)
		ptr->io_num[0] = 1;
	if (ft_strcmp(ptr->op[1], "-") == 0)
	{
		ptr->dup_fd[0] = dup(ptr->io_num[0]);
		close(ptr->io_num[0]);
		return (SUCCESS);
	}
	if (is_number(ptr->op[1]) == SUCCESS)
	{
		ptr->dup_fd[0] = dup(ft_atoi(ptr->op[1]));
		if ((ptr->dup_fd[0] = dup2(ptr->dup_fd[0], ptr->io_num[0])) < 0)
			return (FAILURE);
		return (SUCCESS);
	}
	return (redir_output(ptr));
}
