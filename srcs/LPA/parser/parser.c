/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 11:47:05 by guvillat          #+#    #+#             */
/*   Updated: 2020/03/12 13:15:47 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void		init_parser(t_parser *parser, t_core *shell)
{
	shell->subpts = 0;
	parser->state = P_START;
	parser->f = 4;
	init_start_graph(parser->graph);
	init_redirect_graph(parser->graph);
	init_process_graph(parser->graph);
	init_ionumber_graph(parser->graph);
	init_word_graph(parser->graph);
}

static u_int8_t	parser_error(char *data, t_core *shell)
{
	ft_dprintf(STDERR_FILENO, "42sh: syntax error near unexpected token `%s'\n",
		data);
	shell->subpts = 1;
	return (FALSE);
}

static u_int8_t	p_if(enum e_pstate st, t_core *sh)
{
	if (sh->is_interactive && (st == P_PIPE || st == P_ANDIF || st == P_ORIF))
		return (1);
	return (0);
}

static u_int8_t	parser_graph(t_parser *parser, enum e_pstate id)
{
	return (graph(&parser->state, id, parser->graph[parser->state].good_type));
}

u_int8_t		parser(t_lst *lexer, t_core *shell)
{
	t_parser	p;
	t_lst		*tok_lst;

	if (!lexer)
		return (FALSE);
	tok_lst = lexer;
	init_parser(&p, shell);
	while (tok_lst)
	{
		if (p_if(p.state, shell) && ((t_token*)tok_lst->content)->id == P_END)
		{
			if (shell->subpts)
				return (FALSE);
			if ((p.f = parser_subpts(shell, lexer)) == FALSE)
				continue ;
			else if (p.f == 2)
				return (FALSE);
			else
				break ;
		}
		if (!parser_graph(&p, ((t_token*)tok_lst->content)->id))
			return (parser_error(((t_token*)tok_lst->content)->data, shell));
		tok_lst = tok_lst->next;
	}
	return (TRUE);
}
