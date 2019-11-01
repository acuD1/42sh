
#ifndef ENUM_H
# define ENUM_H

/*
** LEXER_PARSER_ANALYZER
*/

typedef enum analyzer_state
{
    A_START,
    A_SEPARATOR,
    A_REDIRECT,
    A_IONUMBER,
    A_ASSIGN,
    A_WORD,
    A_END,
    A_ERROR,
    A_STOP,
}           e_analyzer_state;

typedef enum    parser_state
{
    P_NEWLINE, // si tok->next = 23 job sinon process si condition ok
    P_ANDIF, // process
    P_AND, // job deamon
    P_ORIF, // process
    P_PIPE, // redir qui att un newline SUBSHELL
    P_DSEMI, // FOR CASE
    P_SEMICOLON, // job
    P_DLESSDASH, // redir
    P_DLESS, // redir
    P_LESSGREAT, // redir
    P_LESSAND, // redir
    P_LESS, // redir
    P_DGREAT, // redir
    P_GREATAND, // redir
    P_GREAT, // redir
    P_TOKEN,
    P_IONUMBER, //ionumber
    P_ASSIGN, // stock dans shell->assign une lst key=value;
    P_WORD, // 
    P_START,
    P_END,
    P_ERROR,
    // P_DBQUOTE,
    // P_QUOTE,
    // P_PARENT_OPEN,
    // P_PARENT_CLOSE,
    // P_BACKQUOTE,
    // P_HOOK_OPEN,
    // P_HOOK_CLOSE,
    // P_BRACKET_OPEN,
    // P_BRACKET_CLOSE,
    // P_HASH,
    // P_PERCENT,
    // P_SPSTRING,
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
}               e_parser_state;

typedef enum    lexer_state {
    START,
    NAME,
    NEWLINE, 
    IO_NUMBER,  
    ASSIGNEMENT_WORD,
    OPERATOR,
    END,
}               e_lexer_state;

#endif