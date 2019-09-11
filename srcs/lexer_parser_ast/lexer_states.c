/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_states.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:23:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/11 17:23:18 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

void end_lexer(t_lexer *lexer)
{
	// printf("END %u\n", lexer->status);
	if (lexer->buff == '\0')
		lexer->status = END;
	else
	{
		lexer->status = START;
		lexer->buf_pos++;
	}
}

void name_lexer(t_lexer *lexer)
{
	int i;

	i = 0;
	if (lexer->buff[lexer->buf_pos])
	{
		i = lexer->buf_pos;
		while (lexer->buff[i] != ' ' || lexer->buff[i] != '\t')
			i++;
		// ft_add_token(&lexer->tok, TOK_WORD, ft_strsub(lexer->buff, lexer->buf_pos, i));
		lexer->buf_pos += i + 1;
	}
	// ft_add_token(lexer->buff, &lexer->tok);
	lexer->ntok++;
	// printf("NAME %u   %s\n", lexer->status, ((t_token*)lexer->tok->content)->id);
	// lexer->status = NAME;
	lexer->status = START;
}

void number_lexer(t_lexer *lexer)
{
	// if end_lexer
	lexer->status = START;
}

void newline_lexer(t_lexer *lexer)
{
	// ft_add_token(lexer->buff, &lexer->tok);
	// lexer->ntok++;
	// printf("NwlinE %u   %s\n", lexer->status, ((t_token*)lexer->tok->content)->id);
	// lexer->status = NEWLINE;
	lexer->status = START;
}
//(const char *buf, size_t *buf_pos, s_token *token)
void operator_lexer(t_lexer *lexer)
{
	static t_token    ope[] =
	  {
	    {TOK_NEWLINE, "\n", 1},
	    {TOK_ANDIF , "&&", 2},
	    {TOK_AND, "&", 1},
	    {TOK_ORIF, "||", 2},
	    {TOK_PIPE, "|", 1},
	    {TOK_DSEMI, ";;", 2},
	    {TOK_SEMICOLON, ";", 1},
	    {TOK_DLESSDASH, "<<-", 3},
	    {TOK_DLESS, "<<", 2},
	    {TOK_LESSGREAT, "<>", 2},
	    {TOK_LESSAND, "<&", 2},
	    {TOK_LESS, "<", 1},
	    {TOK_DGREAT, ">>", 2},
	    {TOK_GREATAND, ">&", 2},
	    {TOK_CLOBBER, ">|", 2},
	    {TOK_GREAT, ">", 1},
	    {TOK_PARENT_OPEN, "(", 1},
	    {TOK_PARENT_CLOSE, ")", 1},
	    {TOKEN, NULL, 0}
	  };
	int i;

	i = 0;
	while (ope[i].id != TOKEN)
	{
		if (!strncmp(lexer->buff, ope[i].data, ope[i].data_len))
		{
			
			    if (lexer->buf_pos)
					lexer->buf_pos += ope[i].data_len;
     			if (lexer->tok)
					token_set(lexer->tok->content, ope[i].id, ope[i].data);
				// printf("%u %s \n", ((t_token*)lexer->tok->content)->id, ((t_token*)lexer->tok->content)->data);
      	}
      	i++;
	}
	lexer->status = START;
}

void assignement_word_lexer(t_lexer *lexer)
{
	// ft_add_token(lexer->buff, &lexer->tok);
	// lexer->ntok++;
	// printf("assi namE %u   %s\n", lexer->status, ((t_token*)lexer->tok->content)->id);
	// lexer->status = ASSIGNEMENT_WORD;
	lexer->status = START;
}



void start_lexer(t_lexer *lexer)
{
	printf("%c\n",lexer->buff[lexer->buf_pos] );
	if (lexer->buff[lexer->buf_pos] == '\0')
		lexer->status = END;
	else if (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
	{
		lexer->io_here = 0;
		while (lexer->buff[lexer->buf_pos] == ' ' || lexer->buff[lexer->buf_pos] == '\t')
			lexer->buf_pos++;
	}
	// else if (ft_isdigit(lexer->buff[lexer->buf_pos]))
		// lexer->status = IO_NUMBER;
	else if (ft_strchr(OPERATORS, lexer->buff[lexer->buf_pos]))
	{
		lexer->status = OPERATOR;
	}
	// else if (ft_strchr(CHAR_INTERRUPT, lexer->buff[buf_pos]))
		// lexer->status = NEWLINE;
	// else if (ft_strchr("=", lexer->buff[buf_pos])) // contien un signe = a la fin
		// lexer->status = ASSIGNEMENT_WORD;
	else
		lexer->status = NAME;
	printf("statu %u\n", lexer->status);
	lexer->buf_pos++;
	// lexer->status = END;
}
