/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:01 by arsciand          #+#    #+#             */
/*   Updated: 2020/05/09 17:28:02 by fcatusse         ###   ########.fr       */
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
# define F_C					"\x1b[35;5;108m"

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
# define MAX_PATH				4096
# define ACCESS_MAX_PATH		1024

/*
** Command Line
*/

# define CREDIT					"arsciand, fcatusse, mpivet-p and guvillat\n"
# define PS1					"'42sh-1.0$ '"
# define PS2					"'> '"
# define BUFF_SIZE				4096
# define READ_SIZE				8
# define QUOTE					'\''
# define DQUOTE					'\"'
# define BQUOTE					'`'
# define NEW_LINE				"\n"
# define SPACE					" "
# define BACKSLASH				'\\'
# define CURLY_BRACE_OPEN		'{'
# define CURLY_BRACE_CLOSE		'}'
# define CMD_PROMPT				0
# define CMD_SUBPROMPT			1
# define CMD_DONE				2
# define SEARCH_FAILURE			29
# define SEARCH_SUCCESS			22

/*
**	Files name
*/

# define FC_TMP_FILE			"/tmp/42sh_fc.tmp"
# define HISTORY_FILE			"./.42sh_history"

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
# define CTRL_N					0x0e00000000000000
# define CTRL_A					0x0100000000000000
# define CTRL_E					0x0500000000000000
# define CTRL_B					0x0200000000000000
# define CTRL_F					0x0600000000000000
# define CTRL_D					0x0400000000000000
# define MOVE_UP				0x1b5b313b32410000
# define MOVE_DOWN				0x1b5b313b32420000
# define SELECT_LEFT			0x1b5b313b36440000
# define SELECT_RIGHT			0x1b5b313b36430000
# define CTRL_K					0x0b00000000000000
# define CTRL_P					0x1000000000000000
# define CTRL_X					0x1800000000000000

/*
**	Builtins
*/

# define HASH_SIZE				256
# define MAX_LOAD_F				0.75
# define FC_ERR1				"42sh: fc: history specification out of range\n"
# define FC_ERR2				"42sh: fc: -e: option requires an argument\n"
# define FC_ERR3				"42sh: fc: no command found\n"
# define FC_USAGE1				"fc: usage: fc [-e ename] [-lnr] [first] [last]"
# define FC_USAGE2				" or fc -s [pat=rep] [command]\n"
# define FC_ERR_FILE			"42sh: fc: failed to open or create file:"
# define FC_OPT					"elnrs0123456789"
# define HASH_USAGE				"hash [-rl] [-p pathname] [-dt] [name ...]"
# define HASH_OPT				"lrpdt"
# define CD_USAGE				"cd [-L|-P] [dir]"
# define CD_OPT					"LP"
# define PWD_USAGE				"pwd [-LP]"
# define PWD_OPT				"LP"
# define PWD_ERR				"pwd: error retrieving current directory:"
# define CHDIR_ERR				"chdir: error retrieving current directory:"
# define CD_ERR					"cd: error retrieving current directory:"
# define GETCWD_ERR				"getcwd: cannot access parent directories:"
# define TEST_INT_EXP			0x001
# define TEST_ARG				0x002
# define TEST_BIN				0x004
# define TEST_UNA				0x006

/*
**	Intern shell variables
*/

# define EXPORT_VAR				0x001
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

/*
**	SIGNAL COMPATIBILITY (LINUX - MACOS)
*/

# ifndef SIGEMT
#  define SIGEMT 0
# endif

# ifndef SIGINFO
#  define SIGINFO 0
# endif

#endif
