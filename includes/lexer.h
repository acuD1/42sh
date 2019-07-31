/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:40:50 by guvillat          #+#    #+#             */
/*   Updated: 2019/07/31 15:41:23 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


t_parser	*lexer(t_core shell, char *line);
t_ast		*parser(t_core shell, t_parser *parser);

typedef struct		quote
{
	const char		*start;
	const size_t		lenstart;
	const char		*stop;
	const size_t		lenstop;
} s_quote;

s_quote	quotes[] =
{
	{"\"", 1, "\"", 1},
	{"'", 1, "'", 1},
	{"`", 1, "`", 1},
	{"${", 2, "}", 1},
	{"$((", 2, "))", 2},
	{"$(", 2, ")", 1},
	{NULL, 0, NULL, 0},
};

#endif LEXER_H
