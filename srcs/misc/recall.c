/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recall.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/01 01:37:25 by mpivet-p          #+#    #+#             */
/*   Updated: 2020/01/28 20:57:17 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

t_core	*get_core(t_core *core)
{
	static t_core	*mem;

	mem = NULL;
	if (core != NULL && mem == NULL)
		mem = core;
	return (mem);
}
