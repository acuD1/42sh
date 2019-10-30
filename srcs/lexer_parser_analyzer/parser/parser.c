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


void		init_start_graph(t_graph *graph)
{
	static e_parser_state tab_good_type[] = {P_WORD, ALL_REDIRECT, P_ASSIGN,
										P_IONUMBER, P_END, P_START, P_ERROR};
										//P_SEMICOLON,
	graph[P_START].good_type = tab_good_type;
	graph[P_NEWLINE].good_type = tab_good_type;
	graph[P_ORIF].good_type = tab_good_type;
	graph[P_ANDIF].good_type = tab_good_type;
}

t_parser 	*ft_init_graph(t_parser *parser)
{
	init_start_graph(parser->graph);
	init_redirect_graph(parser->graph);
	init_assign_graph(parser->graph);
	init_process_graph(parser->graph);
	init_ionumber_graph(parser->graph);
	init_word_graph(parser->graph);
	return (parser);
}

t_parser *ft_init_parser(t_parser *parser)
{
	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		return (NULL);
	parser->state = P_START;
	parser = ft_init_graph(parser);
	return (parser);
}

uint8_t check_lexer_tokens(e_parser_state *current, e_parser_state needed, e_parser_state possible_state[])
{
	uint8_t		i;

	i = 0;
	if (possible_state == NULL)
		return (0);
	while (possible_state[i] != P_ERROR)
	{
		if (needed == possible_state[i])
		{
			*current = needed;
			return (1);
		}
		i++;
	}
	return (0);
}

uint8_t parser(t_core *shell, t_lexer *lexer)
{
	t_parser	*parser;
	t_lst 		*tok_lst;

	parser = NULL;
	tok_lst = lexer->tok;
	if (!lexer || !shell)
		return (FAILURE);
	parser = ft_init_parser(parser);
	while (((t_token*)tok_lst->content)->id != P_END)
	{
		// ft_printf("parser %u       %s   %u\n", parser->state,((t_token*)tok_lst->content)->data, ((t_token*)tok_lst->content)->id);
		if (!(check_lexer_tokens(&parser->state, ((t_token*)tok_lst->content)->id, parser->graph[parser->state].good_type)))
		{
			ft_printf("error parser %u       %s   %u\n", parser->state,((t_token*)tok_lst->content)->data, ((t_token*)tok_lst->content)->id);
			return (FALSE);
			// GESTION DE LERREUR ET SUBPROMPT ET SIGNAUX
		}
		tok_lst = tok_lst->next;
	}
	// ft_printtoklist(lexer);
	return (TRUE);
}
