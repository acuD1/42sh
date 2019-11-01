/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:01 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/17 16:27:02 by fcatusse         ###   ########.fr       */
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
** LEXER_PARSER_ANALYZER
*/

# define NB_OF_OPE 15
# define CHAR_INTERRUPT 			" \t<>|;&\n"
# define OPERATORS 					"&|;><-\n" 
# define NB_LEXER_STATE 7
# define NB_PARSER_STATE 22
# define NB_ANALYZER_STATE 9
# define REDIR                      P_GREAT, P_LESS
# define REDIR_AND                  P_GREATAND, P_LESSAND
# define REDIR_DB                   P_DGREAT, P_DLESS, P_DLESSDASH
# define ALL_REDIRECT               REDIR, REDIR_DB, REDIR_AND
# define IOFILE                     P_GREAT, P_GREATAND, P_LESS, P_LESSAND, P_DGREAT, P_LESSGREAT
# define IOHERE                     P_DLESS, P_DLESSDASH,
#endif
