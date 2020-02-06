/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpivet-p <mpivet-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:28:30 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/29 23:48:43 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/*
** HASH
*/

enum	e_hash
{
	H_DEF,
	H_EXEC,
	H_PATH,
	H_LISTED,
	H_ABORT
};

/*
**  EXPANSION
*/

enum	e_estate
{
	E_QUOTE,
	E_DBQUOTE,
	E_BQUOTE,
	E_TILDEP,
	E_TILDEM,
	E_TILDE,
	E_DBPARENT,
	E_PARENT,
	E_BRACKET,
	E_HOOK,
	E_DOLLAR,
	NB_EXPANSION_STATE
};

/*
** 	LEXER_PARSER_ANALYZER
*/

enum	e_astate
{
	A_START,
	A_SEPARATOR,
	A_REDIRECT,
	A_IONUMBER,
	A_ASSIGN,
	A_WORD,
	A_END,
	A_ERROR,
	A_STOP,
	NB_ANALYZER_STATE
};

enum	e_pstate
{
	P_NEWLINE,
	P_ANDIF,
	P_AND,
	P_ORIF,
	P_PIPE,
	P_DSEMI,
	P_SEMICOLON,
	P_DLESSDASH,
	P_DLESS,
	P_LESSAND,
	P_LESS,
	P_DGREAT,
	P_GREATAND,
	P_GREAT,
	P_OPE_INTERRUPT,
	P_IONUMBER,
	P_ASSIGN,
	P_WORD,
	P_START,
	P_END,
	P_ERROR,
	NB_PARSER_STATE
};

enum    e_lstate {
    L_START,
    L_NAME,
    L_NEWLINE,
    L_IO_NUMBER,
    L_DISCARD,
    L_ASSIGNEMENT_WORD,
    L_OPERATOR,
    L_END,
	NB_LEXER_STATE
};

/*
**	TERMCAPS STRINGS
*/

enum	e_tcaps
{
	DEL_CR,
	SAVE_CR,
	RESTORE_CR,
	KEY_DOWN,
	KEY_UP,
	KEY_RIGHT,
	KEY_LEFT,
	LEFT_MARGIN,
	UP_LEFT_CORNER,
	CLEAR,
	CLR_LINES,
	CLR_EOL,
	CAPS_NBR
};

typedef enum	e_unary
{
	B_UNATEST, C_UNATEST, D_UNATEST, E_UNATEST, F_UNATEST
	, G_UNATEST, LL_UNATEST, P_UNATEST, R_UNATEST, SS_UNATEST, S_UNATEST
	, U_UNATEST, W_UNATEST, X_UNATEST, Z_UNATEST, SAME_BINTEST, DIFF_BINTEST, EQ_BINTEST, NE_BINTEST, GE_BINTEST
	, LT_BINTEST, LE_BINTEST, NB_TESTBLT
}				t_binary;
#endif
