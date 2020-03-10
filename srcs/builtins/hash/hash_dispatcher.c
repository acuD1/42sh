/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_dispatcher.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 16:54:51 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/10 20:28:08 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void	dispatch_to_filler
	(t_core *shell, t_process *process, enum e_hash fmt)
{
	size_t			i;
	static int8_t	(*fill[3])(t_core *, t_process *, enum e_hash, size_t) = {
		fill_default, NULL, fill_path};

	if (fmt == H_EXEC)
	{
		if (fill_exec(shell, process->av[0], process->bin, fmt) != SUCCESS)
		{
			hash_error(&shell->hash);
			return ;
		}
	}
	else
	{
		i = fmt + 1;
		while (process->av[i])
		{
			if (fill[fmt](shell, process, fmt, i) != SUCCESS)
			{
				hash_error(&shell->hash);
				return ;
			}
			i++;
		}
	}
}

void		hash_dispatcher
	(t_core *shell, t_process *process, enum e_hash fmt)
{
	if (fmt == H_EXEC && process->bin == NULL)
		return ;
	if (shell->hash.map == NULL
		&& !(shell->hash.map = ft_memalloc(sizeof(t_lst*) * shell->hash.size)))
	{
		hash_error(&shell->hash);
		return ;
	}
	dispatch_to_filler(shell, process, fmt);
	if (shell->hash.lenght == 0)
		reset_hash(&shell->hash);
}
