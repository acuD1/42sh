/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_signal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 22:26:28 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/04/23 17:31:52 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <sys/wait.h>

int		get_signal(int status)
{
	if (WIFSTOPPED(status))
	{
		return (WSTOPSIG(status));
	}
	else if (WIFSIGNALED(status))
	{
		return (WTERMSIG(status));
	}
	return (0);
}
