/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: user42 <user42@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2020/04/23 17:00:54 by user42           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"
#include <stdlib.h>

u_int8_t		graph(enum e_pstate *c, enum e_pstate n, enum e_pstate ps[])
{
	size_t	i;

	i = 0;
	if (ps == NULL)
		return (0);
	while (ps[i] != P_ERROR)
	{
		if (n == ps[i])
		{
			*c = n;
			return (1);
		}
		i++;
	}
	return (0);
}

static void		init_parser(t_parser *parser)
{
	parser->state = P_START;
	init_start_graph(parser->graph);
	init_redirect_graph(parser->graph);
	init_process_graph(parser->graph);
	init_ionumber_graph(parser->graph);
	init_word_graph(parser->graph);
}

static u_int8_t	parser_error(char *data)
{
	ft_dprintf(STDERR_FILENO, "42sh: syntax error near unexpected token `%s'\n",
		data);
	return (FALSE);
}

static u_int8_t	parser_graph(t_parser *parser, enum e_pstate id)
{
	return (graph(&parser->state, id, parser->graph[parser->state].good_type));
}

u_int8_t		parser(t_lst *lexer)
{
	t_parser	p;
	t_lst		*tok_lst;

	if (!lexer)
		return (FALSE);
	tok_lst = lexer;
	init_parser(&p);
	while (tok_lst)
	{
		if (!parser_graph(&p, ((t_token*)tok_lst->content)->id))
			return (parser_error(((t_token*)tok_lst->content)->data));
		tok_lst = tok_lst->next;
	}
	return (TRUE);
}
