/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tilde_math_exp.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:46:37 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/08 19:07:36 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

char	*exp_get_tilde(const char *string, size_t len)
{
	(void)string;
	(void)len;
	return (ft_strdup("~"));
}

char	*exp_get_tildep(const char *string, size_t len)
{
	(void)string;
	(void)len;
	return (ft_strdup("~+"));
}

char	*exp_get_tildem(const char *string, size_t len)
{
	(void)string;
	(void)len;
	return (ft_strdup("~-"));
}
