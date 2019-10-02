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
** Lexer_parser_ast
*/

typedef struct s_lexer 	t_lexer;
typedef struct s_parser	t_parser;
typedef struct s_ast 	b_ast;
typedef struct s_node 	b_node;


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
	b_ast		*ast;

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

#endif
