/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/09/19 15:33:02 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "sh42.h"
# include "enum.h"

/*
**	Some build data
*/

typedef struct	s_build
{
	u_int8_t	release;
	u_int8_t	version;
	u_int16_t	patch;
	u_int32_t	date;
}				t_build;

/*
** Lexer_parser_analyzer
*/

typedef struct s_lexer 	t_lexer;
typedef struct s_parser	t_parser;
typedef struct s_analyzer t_analyzer;

typedef void    (*t_analyze)(t_analyzer*);
typedef t_analyze t_anal[NB_ANALYZER_STATE][NB_PARSER_STATE];

typedef void (*t_lexing)(t_lexer*);


/*
**	t_db is formated to support environnement variables ; {key} and {value}
*/

typedef struct	s_db
{
	char		*key;
	char		*value;
}				t_db;

/*
**	t_core shares global variables
*/

struct termios	old_t;

typedef struct	s_core
{
	/* structs */
	t_build		build;
	t_db		db;
	t_lst		*lexer;
	t_lst		*job_list;
	t_lst		*assign_list;

	/* init shell */
	//struct termios	new_t;

	/* lists */
	t_lst		*env;

	/* variables */
	char		*buf;
	char		**tokens;		//	ft_strplit of char *line from GNL [BETA]
	char		*bin;			//	dup of the binary found or located [BETA]
	u_int8_t	opt;			//	Options

}				t_core;

/*
**			COMMAND_LINE
*/

typedef struct		s_termcaps
{
	char			*save_cr;
	char			*reset_cr;
	char 			*del;
	char			*clear;
	char			*clr_end;
	char			*clr_lines;
	char			*right;
	char			*left;
	char			*down;
	char			*up;
	char			*ho;
	char			*cr;
}					t_termcaps;

typedef struct		s_read
{
	char			*prompt;
	int				prompt_len;
	int				x_index;
	int				x;
	int				y;
	int				width;
	int				ws_col;
	int				ws_li;
	int				ac;
	int				new_line;
	int				found;
	int				sub_prompt;
	char			*buffer;
	char			**env;
	char			**cmd;
	t_termcaps		*termcaps;
	t_lst			*history;
	t_lst			*history_index;
}					t_read;

/*
** LEXER_PARSER_ANALYZER
*/

typedef struct s_redir
{
    char            *op[2];
    // int             fds[2];
    enum parser_state  type;
    // int             fd_flags; // flags O_RDWR O_CREAT .. 
}               t_redir;

typedef struct            s_process
{
    t_lst               *redir_list;
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
    t_lst              *process_list;
    // struct termios      *term_modes;
    // pid_t               pgid;
    // t_filedesc          fd;
    // int         status; // 1 = running | 0 = stopped par exemple
    e_parser_state type;
}               t_job;

typedef struct  s_analyzer
{
    t_anal              analyze;
    e_analyzer_state    state;
    t_lst	            *lexer;
    t_job               job;
    t_process           process;
    t_redir             redir;
    t_db                db;
    t_lst               *job_list;
    t_lst               *process_list;
    t_lst               *redir_list;
    t_lst               *assign_list;
}               t_analyzer;

typedef struct          s_graph
{
    e_parser_state      *good_type;
}                       t_graph;

typedef struct      s_parser
{
    t_graph         graph[NB_PARSER_STATE];
    e_parser_state  state;
}                   t_parser;

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

#endif
