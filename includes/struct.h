/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/15 16:43:36 by arsciand          #+#    #+#             */
/*   Updated: 2019/10/08 17:51:37 by fcatusse         ###   ########.fr       */
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
**	t_db is formated to support environnement variables ; {key} and {value}
*/

typedef struct		s_db
{
	char		*key;
	char		*value;
}			t_db;

/*
**	t_core shares global variables
*/

struct termios	old_t;

typedef struct	s_core
{
	/* structs */
	t_build		build;
	t_db		db;

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

enum			e_tcaps
{
	DEL_CR,
	SAVE_CR,
	RESTORE_CR,
	KEY_DOWN,
	KEY_UP,
	KEY_RIGHT,
	KEY_LEFT,
	LEFT_MARGIN,
	UP_LEFT_CORNER,
	CLEAR,
	CLR_LINES,
	CLR_EOL,
	CAPS_NBR
};

typedef struct		s_read
{
	char		*prompt;
	int		prompt_len;
	int		x_index;
	int		x;
	int		y;
	int		width;
	int		ws_col;
	int		ws_li;
	int		ac;

	int		new_line;
	int		found;
	int		sub_prompt;

	char		*tcaps[CAPS_NBR];
	char		*buffer;
	char		**cmd;

	t_core		*shell;
	t_lst		*history;
	t_lst		*history_index;
}			t_read;

#endif
