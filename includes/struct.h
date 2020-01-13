/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 17:09:47 by arsciand          #+#    #+#             */
/*   Updated: 2020/01/13 15:18:45 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCT_H
# define STRUCT_H

# include "enum.h"
# include <termios.h>

/*
** CORE
*/

typedef struct s_core		t_core;

typedef struct				s_db
{
	char					*key;
	char					*value;
	u_int8_t				type;
	u_int32_t				hit;
}							t_db;

typedef struct				s_build
{
	u_int8_t				release;
	u_int8_t				version;
	u_int16_t				patch;
	u_int32_t				date;
}							t_build;

typedef struct				s_hash
{
	t_lst					**map;
	u_int32_t				value;
	u_int32_t				size;
	u_int32_t				lenght;
}							t_hash;

typedef struct				s_read
{
	char					prompt[10];
	int						prompt_len;
	int						x_index;
	int						x;
	int						y;
	int						y_li;
	int						width;
	int						ws_col;
	int						ws_li;
	int						ac;

	int						new_line;
	int						found;
	int						sub_prompt;
	int						status;

	char					*tcaps[CAPS_NBR];
	char					*buffer;
	char					*tmp_buff;
	char					**cmd;

	t_core					*shell;
	t_lst					*history;
	t_lst					*history_index;
}							t_read;

struct						s_core
{
	struct termios			old_t;
	struct termios			new_t;
	t_read					term;
	t_build					build;
	t_hash					hash;
	t_db					db;
	t_lst					*running_process;
	t_lst					*env;
	t_lst					*pos_vars;
	t_lst					*lexer;
	t_lst					*job_list;
	int32_t					status;
	int32_t					heredoc;
	u_int8_t				opt;
	u_int8_t				mode;
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
	enum e_pstate			id;
	char					*data;
	size_t					len;
}							t_token;

struct						s_lexer
{
	char					*buff;
	enum e_lstate			status;
	size_t					ntok;
	size_t					buf_pos;
	t_lexing				lex[NB_LEXER_STATE];
	t_token					token;
};

typedef struct				s_job
{
	char					*command;
	t_lst					*process_list;
	enum e_pstate			type;
}							t_job;

typedef struct				s_process
{
	enum e_pstate			type;
	t_lst					*assign_list;
	t_lst					*redir_list;
	char					**av;
	char					*bin;
	pid_t					pid;
}							t_process;

typedef struct				s_redir
{
	enum e_pstate			type;
	char					*heredoc;
	char					*op[2];
	int						io_num[2];
	int						dup_fd;
}							t_redir;

struct						s_analyzer
{
	t_anal					analyze;
	enum e_astate			state;
	t_lst					*lexer;
	t_job					job;
	t_process				process;
	t_redir					redir;
	t_db					db;
	t_lst					*job_list;
	t_lst					*process_list;
	t_lst					*redir_list;
};

/*
** EXP
*/

typedef struct				s_expan
{
	char					*(*machine)(char *, t_core *);
	enum e_pstate			id;
	int						len;
	char					*data;
}							t_expan;

typedef struct				s_lex_exp
{
	t_lst					*(*func)(t_lexer *, enum e_pstate, int, t_lst *);
	enum e_pstate			id;
	int						len;
}							t_lex_exp;

/*
**	INTERN VAR
*/

typedef struct				s_process_var
{
	char					*name;
	pid_t					pid;
	u_int16_t				bck_order;
	u_int16_t				bck_id;
}							t_process_var;

#endif
