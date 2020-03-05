/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:52:21 by arsciand          #+#    #+#             */
/*   Updated: 2020/03/05 03:55:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include <termios.h>
# include "enum.h"

/*
** CORE
*/

typedef struct s_core		t_core;

typedef struct				s_db
{
	char					*key;
	char					*value;
	u_int32_t				hit;
	u_int8_t				type;
	char					pad[3];
}							t_db;

typedef struct				s_build
{
	u_int32_t				date;
	u_int16_t				patch;
	u_int8_t				release;
	u_int8_t				version;
}							t_build;

typedef struct				s_hash
{
	t_lst					**map;
	u_int32_t				value;
	u_int32_t				size;
	u_int32_t				lenght;
	char					pad[4];
}							t_hash;

typedef struct				s_cd
{
	char					*tmp_pwd;
	int						error;
	u_int8_t				pwd_error;
	u_int8_t				dash;
	u_int8_t				no_symbolic;
	char					pad[1];
}							t_cd;

typedef struct				s_read
{
	t_core					*shell;
	t_lst					*history;
	t_lst					*history_index;
	char					**cmd;
	char					*prompt;
	char					*tcaps[CAPS_NBR];
	char					*buffer;
	char					*tmp_buff;
	char					*ac_tmp;
	int						prompt_len;
	int						x_index;
	int						x;
	int						y;
	int						width;
	int						ws_col;
	int						ws_li;
	int						ac;
	int						sub_prompt;
	int						status;
	int						flag;
	char					pad[4];
}							t_read;

struct						s_core
{
	struct termios			old_t;
	struct termios			new_t;
	t_read					term;
	t_build					build;
	t_hash					hash;
	t_db					db;
	t_cd					cd;
	t_lst					*env;
	t_lst					*pos_vars;
	t_lst					*job_list;
	t_lst					*launched_jobs;
	u_int64_t				opt;
	pid_t					pgid;
	int32_t					status;
	int32_t					heredoc;
	int32_t					terminal;
	int8_t					is_interactive;
	int8_t					notified;
	char					pad[6];
};

/*
**	LEXER_PARSER_ANALYZER
*/

typedef struct s_analyzer	t_analyzer;
typedef struct s_lexer		t_lexer;
typedef t_analyzer			*(*t_analyze)(t_analyzer *, t_core *);
typedef t_analyze			t_anal[NB_ANALYZER_STATE][NB_PARSER_STATE];
typedef t_lst				*(*t_lexing)(t_lexer *, t_lst *);

typedef struct				s_graph
{
	enum e_pstate			*good_type;
}							t_graph;

typedef struct				s_parser
{
	t_graph					graph[NB_PARSER_STATE];
	enum e_pstate			state;
}							t_parser;

typedef struct				s_token
{
	char					*data;
	enum e_pstate			id;
	size_t					len;
	char					pad[8];
}							t_token;

struct						s_lexer
{
	t_lexing				lex[NB_LEXER_STATE];
	t_token					token;
	char					*buff;
	enum e_lstate			status;
	size_t					ntok;
	size_t					buf_pos;
	char					pad[8];
};

typedef struct				s_job
{
	t_lst					*process_list;
	char					*command;
	enum e_pstate			type;
	pid_t					pgid;
	int						jobc_id;
	int8_t					notified;
	char					jobc_last;
	char					pad[2];
}							t_job;

typedef struct				s_process
{
	t_lst					*tok_list;
	t_lst					*assign_list;
	t_lst					*redir_list;
	char					**envp;
	char					**av;
	char					*bin;
	char					*command;
	enum e_pstate			type;
	pid_t					pid;
	pid_t					pgid;
	int						pipe[2];
	int						close[2];
	int8_t					completed;
	int8_t					stopped;
	int8_t					status;
	int8_t					blt;
}							t_process;

typedef struct				s_redir
{
	char					*heredoc;
	char					*op[2];
	enum e_pstate			type;
	int						close;
	int						io_num[2];
	int						dup_fd[2];
}							t_redir;

struct						s_analyzer
{
	t_anal					analyze;
	t_job					job;
	t_process				process;
	t_redir					redir;
	t_db					db;
	t_token					tok;
	t_lst					*lexer;
	t_lst					*job_list;
	t_lst					*process_list;
	t_lst					*redir_list;
	enum e_astate			state;
	char					pad[4];
};

typedef struct				s_cmd
{
	char					**av;
	char					*editor;
	int						first;
	int						last;
	int						ac;
	int						fd;
}							t_cmd;

/*
** EXP
*/

typedef struct s_expansion	t_expansion;
typedef char				*(*t_exp)(const char *, t_core *);
typedef t_expansion			*(*t_inhi)(char *, t_core *, t_expansion *);

typedef struct				s_exp_size
{
	char					*(*acab)(char *, enum e_estate id);
	char					*res;
	enum e_estate			id;
}							t_exp_size;

struct						s_expansion
{
	t_exp					sionat[9];
	t_inhi					biteurs[5];
	char					*res;
	enum e_estate			st;
	enum e_estate			quotus;
	int						erience;
	int						index;
	int						discarded;
	char					pad[4];
};

typedef struct				s_exp_token
{
	char					*data;
	enum e_estate			id;
	int						len;
}							t_exp_token;

typedef struct				s_lex_exp
{
	char					*(*fct)(const char *, int);
	enum e_estate			id;
	int						len;
}							t_lex_exp;

#endif
