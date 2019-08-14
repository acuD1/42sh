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

#define NODETYPE(a) (a & (~NODE_DATA))	// get the type of the nodes

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

// typedef struct      s_lexage
// {
//     t_lexage        *(*lexatisation)(t_lexer *);
// }                   t_lexage;


typedef struct 	s_token
{
	char	*id;
	enum nodetype type;
    struct s_token *next;
    struct s_token *prev;
} 				t_token;

typedef struct s_lexer
{
	char			*buff;
	size_t			status;
	size_t			ntok;	
	size_t			szbuff;
    
    t_token	        *tok;
    // t_lexage        *lexatisation;
} 				t_lexer;


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
    