/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_parser_analyzer.h                            :+:      :+:    :+:   */
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
typedef struct s_analyzer t_analyzer;

typedef void    (*t_analyze)(t_analyzer*);
typedef t_analyze t_anal[NB_ANALYZER_STATE][NB_OF_TOKENS];

typedef void (*t_lexing)(t_lexer*);

/*
** ENUM
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
    A_CREATE_JOB,
    A_CREATE_REDIR,
    A_CREATE_PROCESS,
    // A_CMD,
    // A_CMD_ARG,
    // A_IOFILE,
    // A_IO_HERE,
}           e_analyzer_state;

typedef enum    parser_state
{
    P_NEWLINE, // si tok->next = 23 job sinon process si condition ok
    P_ANDIF, // job
    P_AND, // process deamon
    P_ORIF, // job
    P_PIPE, // redir qui att un newline SUBSHELL
    P_DSEMI, // FOR CASE
    P_SEMICOLON, // process
    P_DLESSDASH, // redir
    P_DLESS, // redir
    P_LESSGREAT, // redir
    P_LESSAND, // redir
    P_LESS, // redir
    P_DGREAT, // redir
    P_GREATAND, // redir
    P_GREAT, // redir
    P_TOKEN,
    P_IONUMBER, 
    P_ASSIGN, // stock dans shell->assign une lst key=value;
    P_WORD,
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

/*
** ANALYZER
*/

typedef struct s_redir
{
    char            *op[2];
    // int             fds[2];
    enum parser_state  type;
    // int             fd_flags; // flags O_RDWR O_CREAT .. 
    // int             ionumber;
}               t_redir;

typedef struct            s_process
{
    t_redir             redir;
    t_lst               *ection;
    char                **av;
    enum parser_state  type;

    // char                **env;
    // uint8_t                completed;
    // uint8_t                stopped;
    // pid_t                pid;
    // int                    status;
}                        t_process;

typedef struct s_job
{
    char                *command;
    // char                **cmd; // ancien op[0]
    t_lst              *process_list;
    t_process           process;
    // struct termios      *term_modes;
    // pid_t               pgid;
    // t_filedesc          fd;
    // int         status; // 1 = running | 0 = stopped par exemple
    e_analyzer_state type;
}               t_job;

typedef struct  s_analyzer
{
    t_anal              analyze;
    e_analyzer_state    state;
    // t_lst               *ninjutsu; // dedicace a cedric le S
    t_lexer             *lexer;
    t_process           process;
    t_lst               *job_list;
    t_job               job;
    t_redir             redir;
}               t_analyzer;

void init_redir(t_redir *new);
void init_process(t_process *new);
void init_job(t_job *new);
t_lst *analyzer(t_core *shell);
t_analyzer *init_analyze(t_analyzer *analyzer, t_core *shell);
void cmd_analyze(t_analyzer *analyzer);
void end_analyze(t_analyzer *analyzer);
void separator_analyze(t_analyzer *analyzer);
void redirect_analyze(t_analyzer *analyzer);
void error_analyze(t_analyzer *analyzer);
void ionbr_analyze(t_analyzer *analyzer);
void assign_analyze(t_analyzer *analyzer);
void redir_analyze(t_analyzer *analyzer);
void process_analyze(t_analyzer *analyzer);
void job_analyze(t_analyzer *analyzer);

void    get_token(t_analyzer *analyzer);
t_redir *fetch_redir(t_redir *redir);
t_process *fetch_process(t_process *process);
t_job *fetch_job(t_job *job);
char *ft_jointab(char **tablo);
void ft_printtab(char **cmd);
void printanalyzer(t_analyzer *analyzer);
void ft_printredir(t_redir *redir);
void ft_printprocess(t_process *process);
void ft_printjob(t_job *job);



/*
** PARSER
*/

typedef struct          s_graph
{
    e_parser_state      *good_type;
}                       t_graph;

typedef struct      s_parser
{
    t_graph         graph[NB_OF_TOKENS];
    e_parser_state  state;
}                   t_parser;

uint8_t        parser(t_core *shell, t_lexer *lexer);
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

typedef struct  s_token
{
    e_parser_state id;
    char            *data;
    size_t          data_len;
}              t_token;

typedef struct  s_lexer
{
    char            *buff;
    e_lexer_state   status;
    size_t          ntok;   
    size_t          buf_pos;
    t_lexing        lex[NB_LEXER_STATE];
    size_t          io_here;
    t_lst           *tok;
    t_token         token;
}               t_lexer;

t_lexer         *lexer(char *line);
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
t_lexer			*init_lexer(char *line);
t_token 		*lexer_token_set(t_token *token, e_parser_state opeid, char *data);
t_lst			*ft_create_token(char *data, e_parser_state opeid);

#endif
