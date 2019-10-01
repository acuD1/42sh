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
# include "lexer.h"

typedef struct  s_lexer t_lexer;
typedef struct  s_parser t_parser;
typedef void    (*t_parsing)(t_parser*, t_lexer*);
typedef t_parsing t_pars[NB_PARSER_STATE][NB_OF_TOKENS];

typedef enum	parser_state
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
    P_LESSGREAT,
    P_LESSAND,
    P_LESS,
    P_DGREAT,
    P_GREATAND,
    P_CLOBBER,
    P_GREAT,
    P_TOKEN,
    P_IONUMBER,
    P_ASSIGN,
    P_WORD,
    P_START,
	P_END,
    P_ERROR,
    P_DBQUOTE,
    P_QUOTE,
    P_PARENT_OPEN,
    P_PARENT_CLOSE,
    P_BACKQUOTE,
    P_HOOK_OPEN,
    P_HOOK_CLOSE,
    P_BRACKET_OPEN,
    P_BRACKET_CLOSE,
    P_HASH,
    P_PERCENT,
    P_ANDDGREAT,
    P_ANDGREAT,
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

typedef struct          s_graph
{
    e_parser_state      *good_type;
}                       t_graph;


typedef struct      s_parser
{
    // t_pars          parsing;
    t_graph         graph[NB_OF_TOKENS];

    // t_lst            *tok;
    e_parser_state  state;
}                   t_parser;

void        parser(t_core *shell, t_lexer *lexer);
// void        init_word_graph(t_graph *graph);
// void        init_redirect_graph(t_graph *graph);
// void        init_assign_graph(t_graph *graph);
// void        init_pipe_graph(t_graph *graph);
// void        init_ionumber_graph(t_graph *graph);
// void        init_start_graph(t_graph *graph);
t_parser    *ft_init_graph(t_parser *parser);



#endif
