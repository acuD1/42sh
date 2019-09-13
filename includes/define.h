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

# define BITOK_ERROR	0x001
# define PATH_ERROR		0x002
# define FORK_ERROR		0x004
# define BIN_ERROR		0x006
# define PERM_ERROR		0x008
# define EXEC_ERROR		0x010

/*
**  Lexer Token
*/

# define CHAR_INTERRUPT 			" \t<>|;&!=\n" 
# define OPERATORS 					"&|;><-" 
// # define TOKEN					NULL			
# define T_ESCSEQ				"\\"
# define T_EOF					"EOF"
# define T_DBQUOTE				"\""
# define T_PIPE					"|"
# define T_LPARENT			"("
# define T_RPARENT			")"
# define T_GREAT					">"
# define T_LESS					"<"
# define T_SEMI				";"
# define T_BQUOTE				"`"
# define T_AND					"&"
# define T_LHOOK				"{"
# define T_RHOOK				"}"
# define T_LBRACKET			"["
# define T_RBRACKET			"]"
# define T_HASH					"#"
# define T_PERCENT				"%"
# define T_NEWLINE				"\\n"
# define T_ANDIF					"&&"
# define T_ORIF					"||"
# define T_DSEMI					";;"
# define T_DLESS					"<<"
# define T_DGREAT					">>"
# define T_LESSAND				"<&"
# define T_GREATAND				">&"
# define T_LESSGREAT				"<>"
# define T_ANDDGREAT				"&>>"
# define T_ANDGREAT				"&>"
# define T_DLESSDASH				"<<-"
# define T_CLOBBER				">|"
# define T_DEQ					"=="
# define T_NOTEQ					"!="
// # define TOK_CASE					"case"
// # define TOK_DO						"do"
// # define TOK_DONE					"done"
// # define TOK_ELIF					"elif"
// # define TOK_ELSE					"else"
// # define TOK_ESAC					"esac"
// # define TOK_FI						"fi"
// # define TOK_FOR					"for"
// # define TOK_IF						"if"
// # define TOK_IN						"in"
// # define TOK_THEN					"then"
// # define TOK_UNTIL					"until"
// # define TOK_WHILE					"while"
// # define TOK_IO_NUMBER				"IO number"
// # define TOK_ASSIGN					"assign (=)"
// # define TOK_STRING					"word"
// # define TOK_SPSTRING				"spword"
// # define TOK_END					"end"
// # define TOK_ERROR					"ERROR"
// # define TOK_START					"START"


/*
** LEXER 
*/

#endif
