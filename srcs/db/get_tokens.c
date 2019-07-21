/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/21 13:05:26 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/21 13:06:46 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

int8_t		get_tokens(t_core *shell, char *line)
{
	shell->tokens = ft_strsplit(line, " \t");
	if (shell->tokens == NULL)
		return (FAILURE);
	return (SUCCESS);
}
