/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_lexer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 17:21:39 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/11 17:22:02 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

static void ft_init_lex(t_lexer *lexer)
{
	lexer->lex[START] = start_lexer;
	lexer->lex[OPERATOR] = operator_lexer;
	lexer->lex[NAME] = name_lexer;
	lexer->lex[IO_NUMBER] = number_lexer;
	lexer->lex[NEWLINE] = newline_lexer;
	lexer->lex[ASSIGNEMENT_WORD] = assignement_word_lexer;
	lexer->lex[END] = end_lexer;
}

t_lexer *init_lexer(t_core *shell, char *line)
{
	t_lexer *new;

	if (!line || !shell)
		return (NULL);
	if (!(new = (t_lexer*)malloc(sizeof(t_lexer))))
		return (NULL);
	new->buff = line;
	new->status = START;
	new->ntok = 0;
	new->buf_pos = 0;
	// new->szbuff = ft_strlen(line);
	new->tok = NULL;
	new->io_here = 0;
	ft_init_lex(new);
	// ft_init_machine(new->machina);
	return (new);
}

// static void ft_init_machine(t_machine *machine)
// {
// 	machine[0] = E_DEFAULT;
// 	machine[1] = E_END;
// 	machine[2] = E_NEWLINE;
// 	machine[3] = E_ANDIF;
// 	machine[4] = E_AND;
// 	machine[5] = E_ORIF;
// 	machine[6] = E_PIPE;
// 	machine[7] = E_DSEMI;
// 	machine[9] = E_SEMICOLON;
// 	machine[10] = E_PARENT_OPEN;
// 	machine[11] = E_PARENT_CLOSE;
// 	machine[12] = E_BRACKET_OPEN;
// 	machine[13] = E_BRACKET_CLOSE;
// 	machine[14] = E_HOOK_OPEN;
// 	machine[15] = E_HOOK_OPEN;
// 	ft_init_machine_bis(machine);
// }

// static void ft_init_machine_bis(t_machine *machine)
// {
// 	machine[16] = E_DLESSDASH;
// 	machine[17] = E_DLESS;
// 	machine[18] = E_LESSGREAT;
// 	machine[19] = E_LESSAND;
// 	machine[20] = E_LESS;
// 	machine[21] = E_DGREATt;
// 	machine[22] = E_GREATAND;
// 	machine[23] = E_CLOBBER;
// 	machine[24] = E_GREAT;
// 	machine[25] = E_DBQUOTE;
// 	machine[26] = E_QUOTE;
// 	machine[27] = E_BQUOTE;
// 	machine[28] = E_IONUMBER;
// 	machine[29] = E_ASSIGN;
// 	machine[30] = E_WORD;
// 	machine[31] = E_ERROR;
// }

	// machine[TOK_NEWLINE] = E_NEWLINE;
	// machine[TOK_EOF] = E_END;
	// machine[TOK_ANDIF] = E_ANDIF;
	// machine[TOK_AND] = E_AND;
	// machine[TOK_ORIF] = E_ORIF;
	// machine[TOK_PIPE] = E_PIRE;
	// machine[TOK_DSEMI] = E_DSEMI;
	// machine[TOK_SEMICOLON] = E_SEMICOLON;
	// machine[TOK_PARENT_OPEN] = E_PARENT_OPEN
	// machine[TOK_PARENT_CLOSE] = E_PARENT_CLOSE
	// machine[TOK_BRACKET_OPEN] = E_BRACKET_OPEN
	// machine[TOK_BRACKET_CLOSE] = E_BRACKET_CLOSE
	// machine[TOK_HOOK_OPEN] = E_HOOK_OPEN
	// machine[TOK_HOOK_OPEN] = E_HOOK_OPEN
	// machine[TOK_DLESSDASH] = E_DLESSDASH;
	// machine[TOK_DLESS] = E_DLESS;
	// machine[TOK_LESSGREAT] = E_LESSGREAT;
	// machine[TOK_LESSAND] = E_LESSAND;
	// machine[TOK_LESS] = E_LESS;
	// machine[TOK_DGREAT] = E_DGREATt;
	// machine[TOK_GREATAND] = E_GREATAND;
	// machine[TOK_CLOBBER] = E_CLOBBER;
	// machine[TOK_GREAT] = E_GREAT;
	// machine[TOK_DBQUOTE] = E_DBQUOTE;
	// machine[TOK_QUOTE] = E_QUOTE;
	// machine[TOK_BQUOTE] = E_BQUOTE;
	// machine[TOK_IONUMBER] = E_IONUMBER;
	// machine[TOK_ASSIGN] = E_ASSIGN;
	// machine[TOK_WORD] = E_WORD;
	// machine[TOK_WORD] = E_END;
	// machine[TOK_ERROR] = E_ERROR;






	// machine[TOK_NEWLINE] = token_newline;
	// machine[TOK_EOF] = token_eof;
	// machine[TOK_ANDIF] = token_andif;
	// machine[TOK_AND] = token_and;
	// machine[TOK_ORIF] = token_orif;
	// machine[TOK_PIPE] = token_pipe;
	// machine[TOK_DSEMI] = token_dsemi;
	// machine[TOK_SEMICOLON] = token_semicolon;
	// machine[TOK_PARENT_OPEN] = token_lparent;
	// machine[TOK_PARENT_CLOSE] = token_rparent;
	// machine[TOK_BRACKET_OPEN] = token_lbracket;
	// machine[TOK_BRACKET_CLOSE] = token_rbracket;
	// machine[TOK_HOOK_OPEN] = token_lhook;
	// machine[TOK_HOOK_OPEN] = token_rhook;
	// machine[TOK_DLESSDASH] = token_dlessdash;
	// machine[TOK_DLESS] = token_dless;
	// machine[TOK_LESSGREAT] = token_lessgreat;
	// machine[TOK_LESSAND] = token_lessand;
	// machine[TOK_LESS] = token_less;
	// machine[TOK_DGREAT] = token_dgreat;
	// machine[TOK_GREATAND] = token_greatand;
	// machine[TOK_CLOBBER] = token_clobber;
	// machine[TOK_GREAT] = token_great;
	// machine[TOK_DBQUOTE] = token_dbquote;
	// machine[TOK_QUOTE] = token_quote;
	// machine[TOK_BQUOTE] = token_bquote;
	// machine[TOK_IONUMBER] = token_ionumber;
	// machine[TOK_ASSWD] = token_assignement_word;
	// machine[TOK_WORD] = token_word;