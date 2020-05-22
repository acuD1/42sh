/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:28:30 by fcatusse          #+#    #+#             */
/*   Updated: 2020/05/08 00:16:09 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

enum	e_subp
{
	SP_START,
	SP_DBQUOTE,
	SP_QUOTE,
	SP_BRACEPARAM,
	SP_BACKSLASH,
	SP_END,
	NB_SUBP_STATE,
};

/*
**	HASH
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
**	EXPANSION
*/

enum	e_estate
{
	E_START,
	E_EXP,
	E_WORD,
	E_QUOTES,
	E_DISCARD,
	E_END,
	E_QUOTE,
	E_DBQUOTE,
	E_TILDEP,
	E_TILDEM,
	E_TILDE,
	E_BRACKET,
	E_DOLLAR,
	NB_EXPANSION_STATE
};

/*
**	LEXER_PARSER_ANALYZER
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
	P_ANDDGREAT,
	P_ANDGREAT,
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

enum	e_lstate
{
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
	SELECT_ON,
	SELECT_OFF,
	BELL,
	CAPS_NBR
};

enum	e_unary
{
	B_UNATEST,
	C_UNATEST,
	D_UNATEST,
	E_UNATEST,
	F_UNATEST,
	G_UNATEST,
	LL_UNATEST,
	P_UNATEST,
	R_UNATEST,
	SS_UNATEST,
	S_UNATEST,
	U_UNATEST,
	W_UNATEST,
	X_UNATEST,
	Z_UNATEST,
	SAME_BINTEST,
	DIFF_BINTEST,
	EQ_BINTEST,
	NE_BINTEST,
	GE_BINTEST,
	LT_BINTEST,
	LE_BINTEST,
	NB_TESTBLT
};

/*
**	AUTO COMPLETION
*/

enum	e_ac_type
{
	AC_FILE,
	AC_BINARY,
	AC_VARIABLE,
	AC_BRACKET,
};

#endif
