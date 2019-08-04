/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:09:42 by fcatusse          #+#    #+#             */
/*   Updated: 2019/08/04 14:09:43 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLINE_H
# define CMDLINE_H

# define O_PERMISSIONS		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
# define O_MODE_WR		(O_CREAT | O_TRUNC | O_WRONLY)

# include "sh42.h"
# include "shared_libft.h"
# include <stdint.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <dirent.h>

typedef struct		s_read
{
	char		*prompt;
	int		prompt_len;
	int		x;
	int		y;
	int		width;
	int		ws_col;
	int		ws_li;
	char		buffer[BUFF_SIZE];
	int		x_index;
	int		ac;
	char		**env;
	char		**cmd;
	t_lst		*history;
	t_lst		*history_index;
}			t_read;

/*
** Configuration
*/

void			init_termcaps(void);
uint8_t			init_config(void);
uint8_t			reset_config(void);
t_read			*get_size(t_read *data);

/*
** Prompt
*/

char			*init_prompt(t_read *term);
t_read			*display_prompt(t_read *term);
void			goto_prompt(t_read *line);

/*
** Check Caps and Interpret
*/

uint8_t			check_caps(char *buf, t_read *line);
void			insert_in_buffer(char *buf, t_read *line);
void			insert_char_in_buffer(char buf, t_read *input, int buf_index);
void			insert_str_in_buffer(char *d_name, t_read *input);
int			my_outc(int c);


/*
** Cursor Motion
*/

void			move_right(char *buf, t_read *input);
void			move_left(char *buf, t_read *input);
void			move_key_up(t_read *line);
void			move_key_down(t_read *line);
void			jump_words(char *buf, t_read *line);

/*
** Delete Keys
*/

void			del_key(t_read *line);
void			bs_key(char *buf, t_read *line);

/*
** History
*/

void			save_history(t_read *term);

/*
** Quotes and Multiline
*/

void			check_quotes(t_read *line);

/*
** Auto completion
*/

void			auto_complete_mode(char *buf, t_read *input);
void			walking_path_var(char *buf, char *to_find, t_read *input);
void			to_complete_buffer(char *buf, char *last_buf, char *to_find, t_read *input);
void			display_current_directory(char *buf, t_read *input);
void			delete_last_cmd(char *d_name, t_read *input);

#endif
