/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipes.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/29 11:06:48 by mpivet-p          #+#    #+#             */
/*   Updated: 2019/10/29 12:15:50 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int8_t	pipeline_start(t_core *shell, t_lst *process, int *pipes)
{
	if (dup2(pipes[1], 1) < 0)
}

int8_t	pipeline_end(t_core *shell, t_lst *process, int *pipes)
{
	return (SUCCESS);
}

void	exec_pipeline(t_core *shell, t_lst *process)
{
	int		pipes[2];
}
