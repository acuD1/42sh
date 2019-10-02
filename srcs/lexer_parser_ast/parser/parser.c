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

// void ft_init_word_graph(t_parser)
// {
// 	parser->parsing[P_WORD][P_NEWLINE] = separator_parser;
// 	parser->parsing[P_WORD][P_ANDIF] = redirect_parser;
// 	parser->parsing[P_WORD][P_AND] = redirect_parser;
// 	parser->parsing[P_WORD][P_ORIF] = redirect_parser;
// 	parser->parsing[P_WORD][P_PIPE] = redirect_parser;
// 	parser->parsing[P_WORD][P_DSEMI] = separator_parser;
// 	parser->parsing[P_WORD][P_SEMICOLON] = separator_parser;
// 	parser->parsing[P_WORD][P_DLESSDASH] = redirect_parser;
// 	parser->parsing[P_WORD][P_DLESS] = redirect_parser;
// 	parser->parsing[P_WORD][P_LESSGREAT] = redirect_parser;
// 	parser->parsing[P_WORD][P_LESS] = redirect_parser;
// 	parser->parsing[P_WORD][P_DGREAT] = redirect_parser;
// 	parser->parsing[P_WORD][P_GREATAND] = redirect_parser;
// 	parser->parsing[P_WORD][P_CLOBBER] = redirect_parser;
// 	parser->parsing[P_WORD][P_GREAT] = redirect_parser;
// 	parser->parsing[P_WORD][P_IONUMBER] = ionbr_parser;
// 	parser->parsing[P_WORD][P_ASSIGN] = assign_parser;
// 	parser->parsing[P_WORD][P_WORD] = word_parser;
// 	parser->parsing[P_WORD][P_END] = end_parser;
// }

// void ft_init_end_graph(t_parser)
// {
// 	parser->parsing[P_END][P_NEWLINE] = separator_parser;
// 	parser->parsing[P_END][P_ANDIF] = redirect_parser;
// 	parser->parsing[P_END][P_AND] = redirect_parser;
// 	parser->parsing[P_END][P_ORIF] = redirect_parser;
// 	parser->parsing[P_END][P_PIPE] = redirect_parser;
// 	parser->parsing[P_END][P_DSEMI] = separator_parser;
// 	parser->parsing[P_END][P_SEMICOLON] = separator_parser;
// 	parser->parsing[P_END][P_DLESSDASH] = redirect_parser;
// 	parser->parsing[P_END][P_DLESS] = redirect_parser;
// 	parser->parsing[P_END][P_LESSGREAT] = redirect_parser;
// 	parser->parsing[P_END][P_LESS] = redirect_parser;
// 	parser->parsing[P_END][P_DGREAT] = redirect_parser;
// 	parser->parsing[P_END][P_GREATAND] = redirect_parser;
// 	parser->parsing[P_END][P_CLOBBER] = redirect_parser;
// 	parser->parsing[P_END][P_GREAT] = redirect_parser;
// 	parser->parsing[P_END][P_IONUMBER] = ionbr_parser;
// 	parser->parsing[P_EN7D][P_ASSIGN] = assign_parser;
// 	parser->parsing[P_END][P_WORD] = word_parser;
// 	parser->parsing[P_END][P_END] = end_parser;
// }

void word_parser(t_parser *parser, t_lexer* lexer)
{
	ft_printf("WOWOWORD   %u         %s\n", parser->state, ((t_token*)lexer->tok->content)->data);
	// parser->state = P_WORD;
	//check les prochain token pour savoir si ils sont conforme a la grammaire
	// PB Les tokens sont dans lexer*
}

// void pipe_parser(t_parser *parser, t_lexer* lexer)
// {
// 	init_prompt(t)
// }

void error_parser(t_parser *parser, t_lexer* lexer)
{
	ft_printf("WOWOWORD   %u         %s\n", parser->state, ((t_token*)lexer->tok->content)->data);
}

// void ft_init_start_graph(t_parsing *parser)
// {
// 	parser->parsing[P_START][P_NEWLINE] = separator_parser;
// 	parser->parsing[P_START][P_ANDIF] = redirect_parser;
// 	parser->parsing[P_START][P_AND] = redirect_parser;
// 	parser->parsing[P_START][P_ORIF] = redirect_parser;
// 	parser->parsing[P_START][P_PIPE] = redirect_parser;
// 	parser->parsing[P_START][P_DSEMI] = separator_parser;
// 	parser->parsing[P_START][P_SEMICOLON] = separator_parser;
// 	parser->parsing[P_START][P_DLESSDASH] = redirect_parser;
// 	parser->parsing[P_START][P_DLESS] = redirect_parser;
// 	parser->parsing[P_START][P_LESSGREAT] = redirect_parser;
// 	parser->parsing[P_START][P_LESS] = redirect_parser;
// 	parser->parsing[P_START][P_DGREAT] = redirect_parser;
// 	parser->parsing[P_START][P_GREATAND] = redirect_parser;
// 	parser->parsing[P_START][P_CLOBBER] = redirect_parser;
// 	parser->parsing[P_START][P_GREAT] = redirect_parser;
// 	parser->parsing[P_START][P_IONUMBER] = ionbr_parser;
// 	parser->parsing[P_START][P_ASSIGN] = assign_parser;
	// parser->parsing[P_START][P_WORD] = word_parser;
	// parser->parsing[P_START][P_END] = end_parser;
// }

static void	bzero_parsing(t_pars parsing)
{
	int		index;
	int		state;

	index = 0;
	while (index < NB_PARSER_STATE)
	{
		state = 0;
		while (state < NB_OF_TOKENS)
			parsing[index][state++] = error_parser;
		++index;
	}
}

t_parser *ft_init_parser(t_parser *parser)
{
	if (!(parser = (t_parser*)malloc(sizeof(t_parser))))
		return (NULL);
	parser->state = P_START;
	bzero_parsing(parser->parsing);
	// parser->parsing[P_START][P_WORD] = word_parser;
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
		ft_printf("cu %u ne %u gd %u\n", *current, needed, possible_state[i]);
		if (needed == possible_state[i])
		{
			*current = needed;
			return (1);
		}
		i++;
	}
	return (0);
}

void parser(t_core *shell, t_lexer *lexer)
{
	t_parser	*parser;
	t_lst		**head;

	parser = NULL;
	head = &lexer->tok;
	if (!lexer || !shell)
		return;
	parser = ft_init_parser(parser);
	while (((t_token*)lexer->tok->content)->id != P_END)
	{
		if (!(check_lexer_tokens(&parser->state, ((t_token*)lexer->tok->content)->id, parser->graph[parser->state].good_type)))
		{
			ft_printf("eror %u       %s   %u\n", parser->state,((t_token*)lexer->tok->content)->data, ((t_token*)lexer->tok->content)->id);
			break;
		}
		// parser->parsing[parser->state][((t_token*)lexer->tok->content)->id](parser, lexer);
		lexer->tok = lexer->tok->next;
	}
	if (!lexer->tok)
		lexer->tok = *head;
	shell->ast = ast(lexer);
}
