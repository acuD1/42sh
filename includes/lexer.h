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

#include "parser.h"

typedef struct s_lexer t_lexer;
typedef void (*t_lexing)(t_lexer*);

// typedef enum 	tokenid
// {
// 	TOK_NEWLINE,    // \n
// 	TOK_ANDIF,        // &&
// 	TOK_AND,     // &
// 	TOK_ORIF,     // ||
// 	TOK_PIPE,       // |
// 	TOK_DSEMI,      // ;;
// 	TOK_SEMICOLON,        // ;
// 	TOK_DLESSDASH,  // <<-
// 	TOK_DLESS,      // <<
// 	TOK_LESSGREAT,  // <>
// 	TOK_LESSAND,    // <&
// 	TOK_LESS,       // <
// 	TOK_DGREAT,     // >>
// 	TOK_GREATAND,   // >&
// 	TOK_CLOBBER,    // >|
// 	TOK_GREAT,      // >
// 	TOKEN,          // NULL token
// 	TOK_IONUMBER,   // number juste before '>' or '<'
// 	TOK_ASSIGN,      // assignement_word stringwith an = final
// 	TOK_WORD,      // all others
// } e_tokenid;

typedef enum    lexer_state {
	START,
	NAME,
	NEWLINE, 
	IO_NUMBER,  
	ASSIGNEMENT_WORD,
	OPERATOR,
	END,
}               e_lexer_state;

typedef struct 	s_token
{
	// e_tokenid   	id;
	e_parser_state 	id;
	char        	*data;
	size_t      	data_len;
;} 				t_token;

typedef struct  s_lexer
{
	char			*buff;
	e_lexer_state	status;
	size_t			ntok;	
	// size_t			szbuff;
	size_t          buf_pos;
	t_lexing        lex[NB_LEXER_STATE];
	// t_machine       state[34];
	// enum e_type          last_state;
	size_t          io_here;
	t_lst	        *tok;
	t_token			token;
} 				t_lexer;

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

