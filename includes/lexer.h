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

typedef struct s_lexer t_lexer;
typedef void (*t_lexing)(t_lexer*);

typedef enum 	tokenid
{
	TOK_NEWLINE,    // \n
	TOK_ANDIF,        // &&
	TOK_AND,     // &
	TOK_ORIF,     // ||
	TOK_PIPE,       // |
	TOK_DSEMI,      // ;;
	TOK_SEMICOLON,        // ;
	TOK_DLESSDASH,  // <<-
	TOK_DLESS,      // <<
	TOK_LESSGREAT,  // <>
	TOK_LESSAND,    // <&
	TOK_LESS,       // <
	TOK_DGREAT,     // >>
	TOK_GREATAND,   // >&
	TOK_CLOBBER,    // >|
	TOK_GREAT,      // >
	TOKEN,          // NULL token
	TOK_IONUMBER,   // number juste before '>' or '<'
	TOK_ASSIGN,      // assignement_word stringwith an = final
	TOK_WORD,      // all others
} 				e_tokenid;

typedef enum    state {
	START,
	NAME,
	NEWLINE, 
	IO_NUMBER,  
	ASSIGNEMENT_WORD,
	OPERATOR,
	END,
}               state;

typedef struct 	s_token
{
	e_tokenid   id;
	char        *data;
	size_t      data_len;
;} 				t_token;

typedef struct  s_lexer
{
	char			*buff;
	enum state		status;
	size_t			ntok;	
	// size_t			szbuff;
	size_t          buf_pos;
	t_lexing        lex[7];
	// t_machine       state[34];
	// enum e_type          last_state;
	size_t          io_here;
	t_lst	        *tok;
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
t_lst			*ft_add_token(t_lst **curr, e_tokenid opeid, char *data);
t_lexer			*init_lexer(t_core *shell, char *line);

#endif

