/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 13:28:34 by guvillat          #+#    #+#             */
/*   Updated: 2019/09/19 13:28:35 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

# include "sh42.h" 

typedef struct s_parser t_parser;
typedef int (*t_parsing)(t_parser*);

typedef enum	parser_state
{
    P_START,
	P_END,
    P_ERROR,
    P_DBQUOTE,
    P_QUOTE,
    P_PIPE,
    P_PARENT_OPEN,
    P_PARENT_CLOSE,
    P_GREAT,
    P_LESS,
    P_SEMICOLON,
    P_BACKQUOTE,
    P_AND,
    P_HOOK_OPEN,
    P_HOOK_CLOSE,
    P_BRACKET_OPEN,
    P_BRACKET_CLOSE,
    P_HASH,
    P_PERCENT,
    P_NEWLINE,
    P_ANDIF,
    P_ORIF,
    P_DSEMI,
    P_DLESS,
    P_DGREAT,
    P_LESSAND,
    P_GREATAND,
    P_LESSGREAT,
    P_ANDDGREAT,
    P_ANDGREAT,
    P_DLESSDASH,
    P_CLOBBER,
    P_IONUMBER,
    P_ASSIGN,
    P_WORD,
    P_SPSTRING,
    // P_DEQ,
    // P_NOTEQ,
    // P_CASE,
    // P_DO,
    // P_DONE,
    // P_ELIF,
    // P_ELSE,
    // P_ESAC,
    // P_FI,
    // P_FOR,
    // P_IF,
    // P_IN,
    // P_THEN,
    // P_UNTIL,
    // P_WHILE,
}				e_parser_state;

struct s_parser
{
	t_parsing pars[NB_PARSER_STATE];
};

void parser(t_core *shell, t_lexer *lexer);

#endif
