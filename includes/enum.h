/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enum.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 15:28:30 by fcatusse          #+#    #+#             */
/*   Updated: 2019/12/11 23:35:25 by mpivet-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENUM_H
# define ENUM_H

/*
**  EXPANSION
*/

typedef enum estate
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
    E_QUOTED,
    NB_EXPANSION_STATE
}           e_estate;

/*
** 	LEXER_PARSER_ANALYZER
*/

typedef enum astate
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
}           e_astate;

typedef enum    pstate
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
}               e_pstate;

typedef enum    lstate {
    L_START,
    L_NAME,
    L_NEWLINE,
    L_IO_NUMBER,
    L_DISCARD,
    L_ASSIGNEMENT_WORD,
    L_OPERATOR,
    L_END,
	NB_LEXER_STATE
}               e_lstate;

/*
** 	TERMCAPS STRINGS
*/

enum			e_tcaps
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

#endif
