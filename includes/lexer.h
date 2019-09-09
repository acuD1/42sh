/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/31 15:40:50 by guvillat          #+#    #+#             */
/*   Updated: 2019/07/31 15:41:23 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H


// /*
// ** AST
// */

#define NODETYPE(a) (a & (~NODE_DATA))	// ge7t the type of the nodes


typedef enum operators
{
    TOK_ANDIF,
    TOK_ORIF,
    TOK_DSEMI,
    TOK_DLESS,
    TOK_DGREAT,
    TOK_LESSAND,
    TOK_GREATAND,
    TOK_LESSGREAT,
    TOK_ANDDGREAT,
    TOK_ANDGREAT,
    TOK_DLESSDASH,
} operators;

typedef enum reservedword {
    TOK_IF,
    TOK_THEN,
    TOK_ELSE,
    TOK_ELIF,
    TOK_FI,
    TOK_DO,
    TOK_DONE,
    TOK_CASE,
    TOK_ESAC,
    TOK_WHILE,
    TOK_UNTIL,
    TOK_FOR,
} reservedword;

typedef enum nodetype {
    NODE_NULL           = (0 << 0),
    NODE_PIPE 			= (1 << 0),
    NODE_BCKGRND 		= (1 << 1),
    NODE_SEQ 			= (1 << 2),
    NODE_REDIRECT_IN 	= (1 << 3),
    NODE_REDIRECT_OUT 	= (1 << 4),
    NODE_CMDPATH		= (1 << 5),
    NODE_ARGUMENT		= (1 << 6),
    NODE_DATA 			= (1 << 7),
} nodetype;

typedef enum state {
    START,
    NAME,
    NEWLINE, 
    IO_NUMBER,  
    ASSIGNEMENT_WORD,
    OPERATOR,
    END,
} state;

// typedef struct b_ast
// {
//     int type;
//     char	*data;
//     struct ast* left;
//     struct ast* right;
// } ast;

// void astAttachBinaryBranch (ast *root , ast *leftNode , ast *rightNode);
// void astSetType (ast *node , nodetype nodetype);
// void astSetData (ast *node , char *data );
// void astDelete (ast *node );

/*
** Lexer
*/
// // t_env           *(*func)(char **args, t_env *lst);



typedef struct s_lexer t_lexer;

typedef void (*t_lexing)(t_lexer*);

typedef struct 	s_token
{
	char	*id;
	enum nodetype type;
} 				t_token;

typedef struct s_lexer
{
	char			*buff;
	enum state		status;
	size_t			ntok;	
	size_t			szbuff;
    t_lexing        lex[7];
    size_t          io_here;
    t_lst	        *tok;
} 				t_lexer;

void start_lexer(t_lexer *lexer);
void end_lexer(t_lexer *lexer);
void name_lexer(t_lexer *lexer);
void newline_lexer(t_lexer *lexer);
void number_lexer(t_lexer *lexer);
void assignement_word_lexer(t_lexer *lexer);
void operator_lexer(t_lexer *lexer);
t_lst   *ft_add_token(char *name, t_lst **curr);
// t_ast		*parser(t_core shell, t_parser *parser);

// typedef struct		quote
// {
// 	const char		*start;
// 	const size_t		lenstart;
// 	const char		*stop;
// 	const size_t		lenstop;
// } s_quote;

// s_quote	quotes[] =
// {
// 	{"\"", 1, "\"", 1},
// 	{"'", 1, "'", 1},
// 	{"`", 1, "`", 1},
// 	{"${", 2, "}", 1},
// 	{"$((", 2, "))", 2},
// 	{"$(", 2, ")", 1},
// 	{NULL, 0, NULL, 0},
// };

#endif
    