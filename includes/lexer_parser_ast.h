/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_ast.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/02 18:07:16 by guvillat          #+#    #+#             */
/*   Updated: 2019/10/02 18:07:21 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_PARSER_AST_H
# define LEXER_PARSER_AST_H

# include "sh42.h"

typedef struct s_lexer 	t_lexer;
typedef struct s_parser	t_parser;
typedef struct s_ast 	b_ast;
typedef struct s_node 	b_node;

typedef void (*t_asting)(t_lexer*);
typedef t_asting 	t_ast[NB_AST_STATE];

typedef void    (*t_parsing)(t_parser*, t_lexer*);
typedef t_parsing t_pars[NB_PARSER_STATE][NB_OF_TOKENS];

typedef void (*t_lexing)(t_lexer*);

typedef enum ast_state
{
	B_PROGRAM,
	B_COMPLETE_CMDS,
	B_COMPLETE_CMD,
	B_LIST,
	B_AND_OR,
	B_PIPE_SEQUENCE,
	B_CMD,
	// B_COMPOUND_CMD,
	B_SUBSHELL,
	// B_COMPOUND_LIST,
	// B_TERM,
	// B_FOR_CLAUSE,
	B_NAME,
	// B_IN,
	B_WORDLIST,
	// B_CASE_CLAUSE,
	// B_CASE_LISTS,
	// B_CASE_LIST,
	// B_CASE_ITEMS,
	// B_CASE_ITEM,
	// B_PATTERN,
	// B_IF_CLAUSE,
	// B_ELSE_PART,
	// B_WHILE_CLAUSE,
	// B_UNTIL_CLAUSE,
	// B_FCT_DEFINITION,
	// B_FCT_BODY,	
	// B_FNAME,
	// B_BRACE_GROUP,
	// B_DO_GROUP,
	B_SIMPLE_CMD,
	B_CMD_NAME,
	B_CMD_WORD,
	B_CMD_PREFIX,
	B_CMD_SUFFIX,
	B_REDIRECT_LIST,
	B_IO_REDIRECT,
	B_IO_FILE,
	B_FILENAME,
	B_IO_HERE,
	B_HERE_END,
	B_NEWLINE_LIST,
	B_LINEBREAK,
	B_SEPARATOR_OP,
	B_SEPARATOR,
	B_SEQUENTIAL_SEP,
	B_NEW,
	B_START,
	B_END,
}			e_ast_state;

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

typedef enum    lexer_state {
	START,
	NAME,
	NEWLINE, 
	IO_NUMBER,  
	ASSIGNEMENT_WORD,
	OPERATOR,
	END,
}               e_lexer_state;

typedef struct s_analyze
{
	e_ast_state *machine;
}				t_analyze;

typedef struct s_ast
{
	b_node 		*root;
	t_analyze 	*analyze[NB_AST_STATE];
	e_ast_state state;
}				b_ast;

typedef struct 	s_node
{
	// b_node		*base;
   	e_ast_state type;
    char 		*data;
    size_t 		data_len;
    b_node		*left;
    b_node		*right;
} 				b_node;

typedef struct          s_graph
{
    e_parser_state      *good_type;
}                       t_graph;


typedef struct      s_parser
{
    t_pars          parsing;
    t_graph         graph[NB_OF_TOKENS];

    // t_lst            *tok;
    e_parser_state  state;
}                   t_parser;

typedef struct 	s_token
{
	e_parser_state id;
	char        	*data;
	size_t      	data_len;
;} 				t_token;

typedef struct  s_lexer
{
	char			*buff;
	e_lexer_state	status;
	size_t			ntok;	
	size_t          buf_pos;
	t_lexing        lex[NB_LEXER_STATE];
	size_t          io_here;
	t_lst	        *tok;
	t_token			token;
} 				t_lexer;

/*
** AST
*/


b_node	*ast_add_node(b_node *root, b_node *left, b_node *right, e_ast_state nodetype, char *data);
b_node	*ast_attach_node(b_node *root, b_node *leftnode, b_node *rightnode);
void 	ast_delete(b_node *node);
void error_ast(t_lexer *lexer);
b_ast *init_ast(void);
b_ast *ast(t_lexer *lexer);

/*
** PARSER
*/

void        parser(t_core *shell, t_lexer *lexer);
// void        init_word_graph(t_graph *graph);
// void        init_redirect_graph(t_graph *graph);
// void        init_assign_graph(t_graph *graph);
// void        init_pipe_graph(t_graph *graph);
// void        init_ionumber_graph(t_graph *graph);
// void        init_start_graph(t_graph *graph);
t_parser    *ft_init_graph(t_parser *parser);

/*
** LEXER
*/

int				ft_isdigit(int c);
int 			ft_isalpha(int c);
void			start_lexer(t_lexer *lexer);
void			end_lexer(t_lexer *lexer);
void			name_lexer(t_lexer *lexer);
void			newline_lexer(t_lexer *lexer);
void			number_lexer(t_lexer *lexer);
void			assignement_word_lexer(t_lexer *lexer);
void			operator_lexer(t_lexer *lexer);
void			ft_printtoklist(t_lexer *lexer);
t_lst			*ft_add_token(t_lst **curr, e_parser_state opeid, char *data);
t_lexer			*init_lexer(t_core *shell, char *line);
t_token 		*lexer_token_set(t_token *token, e_parser_state opeid, char *data);
t_lst			*ft_create_token(char *data, e_parser_state opeid);

#endif
