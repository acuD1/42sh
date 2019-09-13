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

// typedef enum operators
// {
//     TOK_ANDIF,
//     TOK_ORIF,
//     TOK_DSEMI,
//     TOK_DLESS,
//     TOK_DGREAT,
//     TOK_LESSAND,
//     TOK_GREATAND,
//     TOK_LESSGREAT,
//     TOK_ANDDGREAT,
//     TOK_ANDGREAT,
//     TOK_DLESSDASH,
//     TOK_NULL,
// } operators;

// typedef enum reservedword {
//     TOK_IF,
//     TOK_THEN,
//     TOK_ELSE,
//     TOK_ELIF,
//     TOK_FI,
//     TOK_DO,
//     TOK_DONE,
//     TOK_CASE,
//     TOK_ESAC,
//     TOK_WHILE,
//     TOK_UNTIL,
//     TOK_FOR,
// } reservedword;


typedef enum    e_type
{
    E_DBQUOTE,
    E_QUOTE,
    E_PIPE,
    E_PARENT_OPEN,
    E_PARENT_CLOSE,
    E_GREAT,
    E_LESS,
    E_SEMICOLON,
    E_BACKQUOTE,
    E_AND,
    E_HOOK_OPEN,
    E_HOOK_CLOSE,
    E_BRACKET_OPEN,
    E_BRACKET_CLOSE,
    E_HASH,
    E_PERCENT,
    E_NEWLINE,
    E_ANDIF,
    E_ORIF,
    E_DSEMI,
    E_DLESS,
    E_DGREAT,
    E_LESSAND,
    E_GREATAND,
    E_LESSGREAT,
    E_ANDDGREAT,
    E_ANDGREAT,
    E_DLESSDASH,
    E_CLOBBER,
    // E_DEQ,
    // E_NOTEQ,
    // E_CASE,
    // E_DO,
    // E_DONE,
    // E_ELIF,
    // E_ELSE,
    // E_ESAC,
    // E_FI,
    // E_FOR,
    // E_IF,
    // E_IN,
    // E_THEN,
    // E_UNTIL,
    // E_WHILE,
    E_IONUMBER,
    E_ASSIGN,
    E_WORD,
    // E_SPSTRING,
    E_END,
    E_ERROR,
    E_START,
}               t_type;


typedef enum        tokenid
  {
    // TOK_EOF,        // EOF
    // TOK_ERROR,
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
    // TOK_DBQUOTE,      // "
    // TOK_QUOTE,      // '
    // TOK_BQUOTE,      // `
    // TOK_PARENT_OPEN,     // (
    // TOK_PARENT_CLOSE,     // )
    // TOK_HOOK_OPEN,     // [
    // TOK_HOOK_CLOSE,     // ]
    // TOK_BRACKET_OPEN,     // {
    // TOK_BRACKET_CLOSE,     // }
    TOKEN,
    TOK_IONUMBER,   // number juste before '>' or '<'
    TOK_ASSIGN,      // assignement_word stringwith an = final
    TOK_WORD,      // all others
  } e_tokenid;

// typedef struct      quote
// {
//     char        *start;
//     size_t      lenstart;
//     char        *stop;
//     size_t      lenstop;
// } s_quote;

// struct s_quote    quotes[] =
//   {
//     {"\"", 1, "\"", 1},
//     {"'", 1, "'", 1},
//     {"`", 1, "`", 1},
//     {"${", 2, "}", 1},
//     {"$((", 2, "))", 2},
//     {"$(", 2, ")", 1},
//     {NULL, 0, NULL, 0},
//   };

// struct s_token quote[] =
// {
//     {TOKEN, NULL, 0},
//     {TOK_PARENT_OPEN, "(", 1},
//     {TOK_PARENT_CLOSE, ")", 1},
//     {TOK_BRACKET_OPEN, "{", 1},
//     {TOK_BRACKET_CLOSE, "}", 1},
//     {TOK_HOOK_OPEN, "[", 1},
//     {TOK_HOOK_CLOSE, "]", 1},
// };

typedef enum state {
    START,
    NAME,
    NEWLINE, 
    IO_NUMBER,  
    ASSIGNEMENT_WORD,
    OPERATOR,
    END,
} state;

typedef struct 	s_token
{
    e_tokenid id;
	char	*data;
    size_t data_len;
;} 				t_token;

typedef struct s_lexer
{
	char			*buff;
	enum state		status;
	size_t			ntok;	
	// size_t			szbuff;
    size_t          buf_pos;
    t_lexing        lex[7];
    // t_machine       state[34];
    enum e_type          last_state;
    size_t          io_here;
    t_lst	        *tok;
} 				t_lexer;

int ft_isdigit(int c);
int ft_isalpha(int c);
void start_lexer(t_lexer *lexer);
void end_lexer(t_lexer *lexer);
void name_lexer(t_lexer *lexer);
void newline_lexer(t_lexer *lexer);
void number_lexer(t_lexer *lexer);
void assignement_word_lexer(t_lexer *lexer);
void operator_lexer(t_lexer *lexer);
void ft_printtoklist(t_lexer *lexer);
t_lst   *ft_add_token(t_lst **curr, e_tokenid opeid, char *data);
t_lexer *init_lexer(t_core *shell, char *line);
void    *token_set(t_token *token, e_tokenid opeid, char *data);
// t_ast		*parser(t_core shell, t_parser *parser);


// #define NODETYPE(a) (a & (~NODE_DATA))   // ge7t the type of the nodes
// typedef struct b_ast
// {
//     int type;
//     char *data;
//     struct ast* left;
//     struct ast* right;
// } ast;

// void astAttachBinaryBranch (ast *root , ast *leftNode , ast *rightNode);
// void astSetType (ast *node , nodetype nodetype);
// void astSetData (ast *node , char *data );
// void astDelete (ast *node );
#endif
    