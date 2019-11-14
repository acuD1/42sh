/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2019/11/12 09:56:11 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

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

uint8_t parser(t_lst *lexer)
{
	t_parser	*parser;
	t_lst 		*tok_lst;
	t_lst 		**head;

	parser = NULL;
	if (!lexer)
		return (FALSE);
	tok_lst = lexer;
	head = &lexer;
	parser = ft_init_parser(parser);
	while (((t_token*)tok_lst->content)->id != P_END)
	{
		// ft_dprintf(2, "parser %u       %s   %u\n", parser->state,((t_token*)tok_lst->content)->data, ((t_token*)tok_lst->content)->id);
		if (!(check_lexer_tokens(&parser->state, ((t_token*)tok_lst->content)->id, parser->graph[parser->state].good_type)))
		{
			ft_dprintf(2, "error parser %u       %s   %u\n", parser->state,((t_token*)tok_lst->content)->data, ((t_token*)tok_lst->content)->id);
			return (FALSE);
			// GESTION DE LERREUR ET SUBPROMPT ET SIGNAUX
		}
		tok_lst = tok_lst->next;
	}
	lexer = *head;
	free(parser);
	return (TRUE);
}
