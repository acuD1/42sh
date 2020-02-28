/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_param_format.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 15:29:22 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/11 15:29:24 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*error_moar_format_third(char **tablo, char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s: %s  syntax error: operand expected\
(error token is \"%s\")\n", tablo[0], data, data);
	ft_tabfree(tablo);
	ft_strdel(&data);
	shell->status = 1;
	return (NULL);
}

char	*error_moar_format_bis(char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s  syntax error: operand expected\
(error token is \":\")\n", data);
	ft_strdel(&data);
	shell->status = 1;
	return (NULL);
}

char	*error_moar_format_param(char **tablo, char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s  syntax error: operand expected (error token is \"%s\")\n",
		data, &data[ft_strlen(tablo[0])
		+ ft_strlen(tablo[1]) + ft_strlen(tablo[2]) + 2]);
	ft_tabfree(tablo);
	ft_strdel(&data);
	shell->status = 1;
	return (NULL);
}
