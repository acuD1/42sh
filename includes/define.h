/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:01 by arsciand          #+#    #+#             */
/*   Updated: 2020/02/19 17:04:01 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINE_H
# define DEFINE_H

/*
**	Global
*/

# define SUCCESS				0
# define FAILURE				-1
# define FALSE					0
# define TRUE					1

/*
**	Color
*/

# define C_R					"\x1b[31m"
# define C_G					"\x1b[32m"
# define C_Y					"\x1b[33m"
# define C_B					"\x1b[34m"
# define C_M					"\x1b[35m"
# define C_C					"\x1b[36m"
# define C_X					"\x1b[0m"
# define C_BOLD					"\x1b[1m"

/*
**	Free
*/

# define FREE_1					1
# define FREE_2					2
# define FREE_ALL				3

/*
**	Option
*/

# define SHELL_OPT				"vhc"
# define FC_OPT					"elnrs0123456789"
# define MAX_PATH				4096
# define ACCESS_MAX_PATH		1024

/*
**	Core
*/

# define I_MODE					0x001
# define NOI_MODE				0x002
# define OPT_MODE				0x004

/*
** Command Line
*/

# define CREDIT					"arsciand, fcatusse, mpivet-p and guvillat\n"
# define PS1					"'42sh-0.1$ '"
# define PS2					"'> '"
# define BUFF_SIZE				4096
# define READ_SIZE				8
# define QUOTE					'\''
# define DQUOTE					'\"'
# define BQUOTE					'`'
# define NEW_LINE				"\n"
# define SPACE					" "
# define BACKSLASH				'\\'
# define BRACKET_OPEN			'('
# define BRACKET_CLOSE			')'
# define CURLY_BRACKET_OPEN		'{'
# define CURLY_BRACKET_CLOSE	'}'
# define CMD_PROMPT				0
# define CMD_SUBPROMPT			1
# define CMD_DONE				2

/*
**	Files name
*/

# define FC_TMP_FILE			"/tmp/42sh_fc.tmp"
# define HISTORY_FILE			"/.42sh_history"

/*
**	Action keys hex masks
*/

# define ARROW_UP				0x1b5b410000000000
# define ARROW_DOWN				0x1b5b420000000000
# define ARROW_RIGHT			0x1b5b430000000000
# define ARROW_LEFT				0x1b5b440000000000
# define BS_KEY					0x7f00000000000000
# define DEL_KEY				0x1b5b337e00000000
# define HOME					0x1b5b480000000000
# define END_LE					0x1b5b460000000000
# define TAB_KEY				0x0900000000000000
# define RETURN_KEY				0x0a00000000000000
# define CTRL_R					0x1200000000000000
# define CTRL_L					0x0c00000000000000
# define CTRL_K					0x0b00000000000000
# define CTRL_A					0x0100000000000000
# define CTRL_E					0x0500000000000000
# define CTRL_B					0x0200000000000000
# define CTRL_F					0x0600000000000000
# define CTRL_D					0x0400000000000000
# define ALT_AW_UP				0x1b1b5b4100000000
# define ALT_AW_DO				0x1b1b5b4200000000

/*
**	Hash table
*/

# define HASH_SIZE				256
# define MAX_LOAD_F				0.75
# define HASH_USAGE				"[-rl] [-p pathname] [-dt] [name ...]"
# define HASH_OPT				"lrpdt"

/*
**	Intern shell variables
*/

# define ENV_VAR				0x001
# define INTERNAL_VAR			0x002
# define SPECIAL_VAR			0x004
# define HIST_SIZE				500
# define HISTFILE_SIZE			500

/*
**	LEXER_PARSER_ANALYZER
*/

# define NB_OF_EXP				12
# define CHAR_INTERRUPT 		" \t<>|;&\n"
# define OPERATORS				"&|;><"

#endif
