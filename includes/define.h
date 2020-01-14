/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/12/19 10:39:03 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
**	Global
*/

# define SUCCESS		0
# define FAILURE		-1
# define FALSE			0
# define TRUE			1

/*
**	Color
*/

# define C_R			"\x1b[31m"
# define C_G			"\x1b[32m"
# define C_Y			"\x1b[33m"
# define C_B			"\x1b[34m"
# define C_M			"\x1b[35m"
# define C_C			"\x1b[36m"
# define C_X			"\x1b[0m"
# define C_BOLD			"\x1b[1m"

/*
**	Free
*/

# define FREE_1			1
# define FREE_2			2
# define FREE_ALL		3

/*
**	Option
*/

# define OPT_VERS		0x001
# define OPT_HELP		0x002
# define MAX_PATH			4096
# define ACCESS_MAX_PATH	4096

/*
**	Exec
*/

# define BLT_NUMBER		0x004
# define BITOK_ERROR	0x001
# define PATH_ERROR		0x002
# define FORK_ERROR		0x004
# define BIN_ERROR		0x006
# define PERM_ERROR		0x008
# define EXEC_ERROR		0x010

/*
**	Command Line
*/

# define S_USR_RW		(S_IRUSR | S_IWUSR)
# define S_GRP_OTH_R		(S_IRGRP | S_IROTH)
# define MODE_WRITE		(O_CREAT | O_WRONLY | O_TRUNC)
# define PS1			"42sh-2.0$ "
# define PS2			"> "
# define BUFF_SIZE		4096
# define READ_SIZE		10
# define HISTORY_FILE		"./.42sh_history"
# define QUOTE			'\''
# define DQUOTE			'\"'
# define BQUOTE			'`'
# define NEW_LINE		'\n'
# define SPACE			" "
# define BACKSLASH		'\\'
# define BRACKET_OPEN		'('
# define BRACKET_CLOSE		')'
# define CURLY_BRACKET_OPEN	'{'
# define CURLY_BRACKET_CLOSE	'}'
# define HOOK_OPEN		'['
# define HOOK_CLOSE		']'

# define CMD_PROMPT		0
# define CMD_SUBPROMPT	1
# define CMD_DONE		2

/*
**		Action keys hex masks
*/

# define ARROW_UP		0x1b5b410000000000
# define ARROW_DOWN		0x1b5b420000000000
# define ARROW_RIGHT	0x1b5b430000000000
# define ARROW_LEFT		0x1b5b440000000000
# define BS_KEY			0x7f00000000000000
# define DEL_KEY		0x1b5b337e00000000
# define HOME			0x1b5b480000000000
# define END_LE			0x1b5b460000000000
# define TAB_KEY		0x0900000000000000
# define RETURN_KEY		0x0a00000000000000
# define CTRL_R			0x1200000000000000
# define CTRL_L			0x0c00000000000000
# define CTRL_K			0x0b00000000000000
# define CTRL_A			0x0100000000000000
# define CTRL_E			0x0500000000000000
# define CTRL_B			0x0200000000000000
# define CTRL_F			0x0600000000000000
# define CTRL_D			0x0400000000000000
# define ALT_AW_UP		0x1b1b5b4100000000
# define ALT_AW_DO		0x1b1b5b4200000000

/*
**	Hash table
*/

# define HASH_SIZE		1
# define MAX_LOAD_F		0.75
# define HASH_DEFAULT	0x001
# define HASH_LISTED	0x002
# define HASH_PATH		0x004
# define HASH_ABORT		0x006

/*
**	===========================================================================
**	INTERN SHELL VARIABLES.....................................................
**	===========================================================================
*/

# define ENV_VAR		0x001
# define INTERNAL_VAR		0x002
# define SPECIAL_VAR		0x004

# define HIST_SIZE		500
# define HISTFILE_SIZE		500

# define DBGMAX(a, b)	dprintf(open(b, O_RDONLY), "%s", a);

/*
** LEXER_PARSER_ANALYZER
*/

# define NB_OF_OPE 14
# define NB_OF_EXP 9
# define CHAR_INTERRUPT 			" \t<>|;&\n"
# define OPERATORS 					"&|;><"
# define EXPANSION 					"$~"
# define REDIR                      P_GREAT, P_LESS
# define REDIR_AND                  P_GREATAND, P_LESSAND
# define REDIR_DB                   P_DGREAT
# define HEREDC						P_DLESS, P_DLESSDASH
# define ALL_REDIRECT               REDIR, REDIR_DB, REDIR_AND, HEREDC
# define ALL_EXPANSION              P_PARENT, P_BRACKET, P_DBPARENT, P_DOLLAR, P_TILDE, P_TILDEP, P_TILDEM
# define ALL_WORDS   	           	P_WORD, P_DBQUOTE, P_QUOTE, P_BQUOTE, P_PARENT, P_BRACKET, P_DBPARENT, P_DOLLAR, P_TILDE, P_TILDEP, P_TILDEM
# define QUOTES   	           	P_DBQUOTE, P_QUOTE, P_BQUOTE

# define IOFILE                     P_GREAT, P_GREATAND, P_LESS, P_LESSAND, P_DGREAT
# define IOHERE                     P_DLESS, P_DLESSDASH
#endif
