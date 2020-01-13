/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2020/01/13 08:29:14 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void			init_start_graph(t_graph *graph)
{
	static enum e_pstate tab_good_type[] = {ALL_WORDS, P_ESCSEQ, ALL_REDIRECT,
		P_ASSIGN, ALL_EXPANSION, P_IONUMBER, P_END, P_START, P_ERROR};

	graph[P_START].good_type = tab_good_type;
	graph[P_NEWLINE].good_type = tab_good_type;
	graph[P_ORIF].good_type = tab_good_type;
	graph[P_ANDIF].good_type = tab_good_type;
}

void			init_exp_graph(t_graph *graph)
{
	static enum e_pstate tab_good_type[] = {P_NEWLINE, ALL_WORDS, ALL_REDIRECT,
		P_ASSIGN, P_IONUMBER, P_PIPE, P_AND, P_END, P_SEMICOLON,
		P_ANDIF, P_ORIF, P_ESCSEQ, ALL_EXPANSION, P_ERROR};

	graph[P_PARENT].good_type = tab_good_type;
	graph[P_DBPARENT].good_type = tab_good_type;
	graph[P_BRACKET].good_type = tab_good_type;
	graph[P_HOOK].good_type = tab_good_type;
	graph[P_TILDE].good_type = tab_good_type;
	graph[P_DOLLAR].good_type = tab_good_type;
}

t_parser		*ft_init_graph(t_parser *parser)
{
	init_start_graph(parser->graph);
	init_redirect_graph(parser->graph);
	init_assign_graph(parser->graph);
	init_process_graph(parser->graph);
	init_ionumber_graph(parser->graph);
	init_word_graph(parser->graph);
	init_exp_graph(parser->graph);
	return (parser);
}

uint8_t			graph(enum e_pstate *c, enum e_pstate n, enum e_pstate ps[])
{
	uint8_t		i;

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

uint8_t			parser(t_lst *lexer)
{
	t_parser	*parser;
	t_lst		*tok_lst;
	t_lst		**head;

	parser = NULL;
	if (!lexer)
		return (FALSE);
	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		return (FALSE);
	parser->state = P_START;
	tok_lst = lexer;
	head = &lexer;
	parser = ft_init_graph(parser);
	while (((t_token*)tok_lst->content)->id != P_END)
	{
		if (!(graph(&parser->state, ((t_token*)tok_lst->content)->id,
			parser->graph[parser->state].good_type)))
		{
			return (FALSE);
		}
		tok_lst = tok_lst->next;
	}
	lexer = *head;
	free(parser);
	return (TRUE);
}
