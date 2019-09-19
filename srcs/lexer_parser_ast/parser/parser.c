/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/19 11:47:17 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void ft_init_parser(t_parser *parser)
{

}

void parser(t_core *shell, t_lexer *lexer)
{
	t_parser *parser;

	parser = NULL;
	if (!lexer || !shell)
		return;
	ft_init_parser(parser);
	(void)shell;
	(void)lexer;
}


