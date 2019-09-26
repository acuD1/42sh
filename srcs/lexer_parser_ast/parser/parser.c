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
// 	parser->parsing[P_WORD][TOK_NEWLINE] = separator_parser;
// 	parser->parsing[P_WORD][TOK_ANDIF] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_AND] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_ORIF] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_PIPE] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_DSEMI] = separator_parser;
// 	parser->parsing[P_WORD][TOK_SEMICOLON] = separator_parser;
// 	parser->parsing[P_WORD][TOK_DLESSDASH] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_DLESS] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_LESSGREAT] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_LESS] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_DGREAT] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_GREATAND] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_CLOBBER] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_GREAT] = redirect_parser;
// 	parser->parsing[P_WORD][TOK_IONUMBER] = ionbr_parser;
// 	parser->parsing[P_WORD][TOK_ASSIGN] = assign_parser;
// 	parser->parsing[P_WORD][TOK_WORD] = word_parser;
// 	parser->parsing[P_WORD][TOKEN] = end_parser;
// }

// void ft_init_end_graph(t_parser)
// {
// 	parser->parsing[P_END][TOK_NEWLINE] = separator_parser;
// 	parser->parsing[P_END][TOK_ANDIF] = redirect_parser;
// 	parser->parsing[P_END][TOK_AND] = redirect_parser;
// 	parser->parsing[P_END][TOK_ORIF] = redirect_parser;
// 	parser->parsing[P_END][TOK_PIPE] = redirect_parser;
// 	parser->parsing[P_END][TOK_DSEMI] = separator_parser;
// 	parser->parsing[P_END][TOK_SEMICOLON] = separator_parser;
// 	parser->parsing[P_END][TOK_DLESSDASH] = redirect_parser;
// 	parser->parsing[P_END][TOK_DLESS] = redirect_parser;
// 	parser->parsing[P_END][TOK_LESSGREAT] = redirect_parser;
// 	parser->parsing[P_END][TOK_LESS] = redirect_parser;
// 	parser->parsing[P_END][TOK_DGREAT] = redirect_parser;
// 	parser->parsing[P_END][TOK_GREATAND] = redirect_parser;
// 	parser->parsing[P_END][TOK_CLOBBER] = redirect_parser;
// 	parser->parsing[P_END][TOK_GREAT] = redirect_parser;
// 	parser->parsing[P_END][TOK_IONUMBER] = ionbr_parser;
// 	parser->parsing[P_END][TOK_ASSIGN] = assign_parser;
// 	parser->parsing[P_END][TOK_WORD] = word_parser;
// 	parser->parsing[P_END][TOKEN] = end_parser;
// }
void word_parser(t_parser *parser, t_lexer* lexer)
{
	ft_printf("WOWOWORD   %u         %s\n", parser->state, ((t_token*)lexer->tok->content)->data);
	// parser->state = P_WORD;
	//check les prochain token pour savoir si ils sont conforme a la grammaire
	// PB Les tokens sont dans lexer*
}

void error_parser(t_parser *parser, t_lexer* lexer)
{
	ft_printf("EROOROROROR   %u         %s\n", parser->state, ((t_token*)lexer->tok->content)->data);
}

// void ft_init_start_graph(t_parsing *parser)
// {
// 	parser->parsing[P_START][TOK_NEWLINE] = separator_parser;
// 	parser->parsing[P_START][TOK_ANDIF] = redirect_parser;
// 	parser->parsing[P_START][TOK_AND] = redirect_parser;
// 	parser->parsing[P_START][TOK_ORIF] = redirect_parser;
// 	parser->parsing[P_START][TOK_PIPE] = redirect_parser;
// 	parser->parsing[P_START][TOK_DSEMI] = separator_parser;
// 	parser->parsing[P_START][TOK_SEMICOLON] = separator_parser;
// 	parser->parsing[P_START][TOK_DLESSDASH] = redirect_parser;
// 	parser->parsing[P_START][TOK_DLESS] = redirect_parser;
// 	parser->parsing[P_START][TOK_LESSGREAT] = redirect_parser;
// 	parser->parsing[P_START][TOK_LESS] = redirect_parser;
// 	parser->parsing[P_START][TOK_DGREAT] = redirect_parser;
// 	parser->parsing[P_START][TOK_GREATAND] = redirect_parser;
// 	parser->parsing[P_START][TOK_CLOBBER] = redirect_parser;
// 	parser->parsing[P_START][TOK_GREAT] = redirect_parser;
// 	parser->parsing[P_START][TOK_IONUMBER] = ionbr_parser;
// 	parser->parsing[P_START][TOK_ASSIGN] = assign_parser;
	// parser->parsing[P_START][TOK_WORD] = word_parser;
	// parser->parsing[P_START][TOKEN] = end_parser;
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
	parser->parsing[P_START][TOK_WORD] = word_parser;
	ft_init_graph(parser);
	return (parser);
}

// int check_lexer_tokens(e_tokenid current, e_tokenid next, )

void parser(t_core *shell, t_lexer *lexer)
{
	t_parser	*parser;

	parser = NULL;
	if (!lexer || !shell)
		return;
	parser = ft_init_parser(parser);
	while (((t_token*)lexer->tok->content)->id != TOKEN)
	{
		ft_printf("%u       %s   %zu\n", parser->state,((t_token*)lexer->tok->content)->data, ((t_token*)lexer->tok->content)->id);
		parser->parsing[parser->state][((t_token*)lexer->tok->content)->id](parser, lexer);
		lexer->tok = lexer->tok->next;
	}
}
