/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:09:42 by fcatusse          #+#    #+#             */
/*   Updated: 2019/09/09 18:53:55 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLINE_H
# define CMDLINE_H

# include "sh42.h"
# include "shared_libft.h"
# include <stdint.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <dirent.h>

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
	char			buffer[BUFF_SIZE];
	char			**env;
	char			**cmd;
	t_lst			*history;
	t_lst			*history_index;
}					t_read;

/*
**		Configuration
*/

void			init_termcaps(void);
uint8_t			init_config(void);
uint8_t			reset_config(t_read *input);
t_read			*get_size(t_read *data);

/*
**		Prompt/Subprompt
*/

char			*init_prompt(t_read *term);
t_read			*display_prompt(t_read *term);
void			goto_prompt(t_read *line);
void			display_subprompt(t_read *term, char quote);
void			goto_subprompt(t_read *line);

/*
**		Check Caps and Interpret
*/

uint8_t			check_caps(char *buf, t_read *line);
void			insert_in_buffer(char *buf, t_read *line);
void			insert_char_in_buffer(char buf, t_read *input, int buf_index);
void			insert_str_in_buffer(char *d_name, t_read *input);
void			insert_newline_in_buff(t_read *line);

/*
**		Cursor Motion
*/

void			move_right(char *buf, t_read *input);
void			move_left(char *buf, t_read *input);
void			move_key_up(t_read *line);
void			move_key_down(t_read *line);
void			move_in_column(char *buff, t_read *line);
void			jump_words(char *buf, t_read *line);

/*
**		Delete Keys
*/

void			del_key(t_read *line);
void			bs_key(char *buf, t_read *line);
void			clr_screen(t_read *input);

/*
**		History
*/

void			init_history(t_read *term);
void			save_history(t_read *term);
void			free_history(t_lst *history);
void			research_mode(t_read **line);
void			write_history(t_read *line);

/*
**		Quotes and Subprompt/Multiline
*/

uint8_t			check_quotes(t_read *line);
void			load_subprompt(char quote, t_read *line);

/*
**		Auto completion
*/

void			auto_complete_mode(char *buf, t_read *input);
void			walking_path_var(char *buf, char *to_find, t_read *input);
void			to_complete_buffer(char *buf, char *last_buf, char *to_find, t_read *input);
void			display_current_directory(char *buf, t_read *input, char *dir);
void			delete_last_cmd(char *d_name, t_read *input);
uint8_t			is_dir(char *dir);

/*
**		Utils
*/

int				my_outc(int c);
uint8_t			get_width_last_line(t_read *input);
uint8_t			get_width_current_line(t_read *input);
uint8_t			newline_count(char *buffer);
void			remove_newline(t_read *line);
uint8_t			is_dot(char *d_name);

/*
**		Functions safe
*/

void		xtputs(char *str, int i, int (*f)(int));
char		*xtgetstr(char *id, char **area);
size_t		xread(int fd, char *buff, int size);

#endif
