/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   struct.h										   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: arsciand <arsciand@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2019/06/15 16:43:36 by arsciand		  #+#	#+#			 */
/*   Updated: 2020/02/01 18:02:52 by mpivet-p         ###   ########.fr       */
/*																			*/
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
//	int						y_li;
	int						width;
	int						ws_col;
	int						ws_li;
	int						ac;

//	int						new_line;
//	int						found;
	int						sub_prompt;
	int						status;

	int						flag;
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
//	t_lst					*lexer;
	t_lst					*job_list;
	t_lst					*launched_jobs;
	u_int64_t				opt;
	int32_t					status;
	int32_t					heredoc;
	int32_t					terminal;
	u_int8_t				mode;
	pid_t					pgid;
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
//	struct termios			tmodes;
	enum e_pstate			type;
	int8_t					notified;
	t_lst					*process_list;
	pid_t					pgid;
	char					*command;
	int						jobc_id;
	char					jobc_last;
}							t_job;

typedef struct				s_process
{
	enum e_pstate			type;
	int8_t					completed;
	int8_t					stopped;
	int8_t					status;
	t_lst					*tok_list;
	t_lst					*assign_list;
	t_lst					*redir_list;
	pid_t					pid;
	pid_t					pgid;
	char					**av;
	char					*bin;
	char					*command;
}							t_process;

typedef struct				s_redir
{
	enum e_pstate			type;
	char					*heredoc;
	char					*op[2];
	int						io_num[2];
	int						dup_fd[2];
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
	t_token					tok;
	t_lst					*job_list;
	t_lst					*process_list;
	t_lst					*redir_list;
};

/*
** EXP
*/

typedef char				*(*t_exp)(char *, t_core *);

typedef struct				s_exp_size
{
	char					*(*acab)(char *, enum e_estate id);
	enum e_estate			id;
	char					*res;
}							t_exp_size;

typedef struct				s_expansion
{
	int						erience;
	t_exp					sionat[10];
}							t_expansion;

typedef struct				s_exp_token
{
	enum e_estate			id;
	char					*data;
	int						len;
}							t_exp_token;

typedef struct				s_lex_exp
{
	char					*(*fct)(char *, int);
	enum e_estate			id;
	int						len;
}							t_lex_exp;

#endif
