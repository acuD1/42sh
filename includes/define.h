/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/07/31 15:47:30 by guvillat         ###   ########.fr       */
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

/*
**	Exec handler
*/

# define BITOK_ERROR		0x001
# define PATH_ERROR		0x002
# define FORK_ERROR		0x004
# define BIN_ERROR		0x006
# define PERM_ERROR		0x008
# define EXEC_ERROR		0x010

/*
**  Lexer Token
*/

# define TOK_ESCSEQ					"\\"
# define TOK_EOF					"EOF"
# define TOK_DB_QUOTE				"\""
# define TOK_PIPE					"|"
# define TOK_PARENT_OPEN			"("
# define TOK_PARENT_CLOSE			")"
# define TOK_GREAT					">"
# define TOK_LESS					"<"
# define TOK_SEMICOLON				";"
# define TOK_BACKQUOTE				"`"
# define TOK_AND					"&"
# define TOK_HOOK_OPEN				"{"
# define TOK_HOOK_CLOSE				"}"
# define TOK_BRACKET_OPEN			"["
# define TOK_BRACKET_CLOSE			"]"
# define TOK_HASH					"#"
# define TOK_PERCENT				"%"
# define TOK_NEWLINE				"\\n"
# define TOK_DAND					"&&"
# define TOK_OR						"||"
# define TOK_DSEMI					";;"
# define TOK_DLESS					"<<"
# define TOK_DGREAT					">>"
# define TOK_LESSAND				"<&"
# define TOK_GREATAND				">&"
# define TOK_LESSGREAT				"<>"
# define TOK_ANDDGREAT				"&>>"
# define TOK_ANDGREAT				"&>"
# define TOK_DLESSDASH				"<<-"
# define TOK_CLOBBER				">|"
# define TOK_DEQ					"=="
# define TOK_NOTEQ					"!="
# define TOK_CASE					"case"
# define TOK_DO						"do"
# define TOK_DONE					"done"
# define TOK_ELIF					"elif"
# define TOK_ELSE					"else"
# define TOK_ESAC					"esac"
# define TOK_FI						"fi"
# define TOK_FOR					"for"
# define TOK_IF						"if"
# define TOK_IN						"in"
# define TOK_THEN					"then"
# define TOK_UNTIL					"until"
# define TOK_WHILE					"while"
# define TOK_IO_NUMBER				"IO number"
# define TOK_ASSIGN					"assign (=)"
# define TOK_STRING					"word"
# define TOK_SPSTRING				"spword"
# define TOK_END					"end"
# define TOK_ERROR					"ERROR"
# define TOK_START					"START"

#endif
