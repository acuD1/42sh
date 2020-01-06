/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:09:42 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/06 14:01:26 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

# include "sh42.h"
# include "shared_libft.h"
# include <stdint.h>
# include <termios.h>
# include <term.h>
# include <termcap.h>
# include <dirent.h>

/*
**		Configuration
*/

void			init_termcaps(t_read *term);
void			init_cmd_line(t_core *shell, t_read *term);
u_int8_t		init_config(t_core *shell);
u_int8_t		reset_config(t_core *shell);
int8_t			get_size(t_read *term);

/*
**		Prompt/Subprompt
*/

void			init_prompt(t_core *shell);
void			display_prompt(t_read *term);
void			goto_prompt(t_read *term);
void			display_subprompt(t_read *term, char *prompt);
void			goto_subprompt(t_read *term);

/*
**		Check Caps and Interpret
*/

uint8_t			check_caps(char *buf, t_read *term);
void			insert_in_buffer(char *buf, t_read *term);
void			insert_char_in_buffer(char buf, t_read *term, int buf_index);
void			insert_str_in_buffer(char *d_name, t_read *term);
void			insert_newline_in_buff(t_read *term);

/*
**		Cursor Motion
*/

void			move_right(char *buf, t_read *term);
void			move_left(char *buf, t_read *term);
void			move_key_up(t_read *term);
void			move_key_down(t_read *term);
void			move_in_column(uint64_t value, t_read *term);
void			jump_words(char *buf, t_read *term, uint64_t value);

/*
**		Delete Keys
*/

void			del_key(t_read *term);
void			bs_key(char *buf, t_read *term);
void			clr_screen(t_read *term);

/*
**		History
*/

int8_t			init_history(t_read *term);
void			save_history(t_read *term);
void			research_mode(t_read *term);
int8_t			write_history(t_read *term);
void			check_expansions(t_read *term);
void			call_number(t_read *term, int i);
void			callback_number(t_read *term, int i);
void			call_word(t_read *term, int i);
void			last_cmd_back(t_read *term, int i);

/*
**		Quotes and Subprompt/Multiline
*/

uint8_t			check_subprompt(t_read *term);
uint8_t			charset_count(t_read *term, char charset, int i);
uint8_t			quotes_is_matching(t_read *term, char *quote);
uint8_t			check_backslash(t_read *term, char *quote);
void			load_subprompt(char quote, t_read *term);

/*
**		Auto completion
*/

void			auto_complete_mode(t_read *term);
void			read_directories(char *to_find, t_read *term);
void			to_complete_bin(char *to_find, t_read *term);
void			to_complete_buffer(char *to_find, t_read *term);
void			display_current_directory(t_read *term, char *dir);
void			delete_last_cmd(char *d_name, t_read *term);
void			parse_env(char **prev_b, char *to_find, t_read *term);
char			**split_path(t_core *shell, char *str);
uint8_t			read_again(char **prev_b, char *path, char *name, t_read *term);

/*
**		Utils/Tools
*/

int				my_outc(int c);
uint8_t			get_width_last_line(t_read *term);
uint8_t			get_width_current_line(t_read *term);
uint64_t		get_mask(char *buff);
int				is_dot(char *d_name);
uint8_t			is_tab(char *d_name, t_read *term);
uint8_t			is_dir(char *dir);

/*
**		Functions safe
*/

void			xtputs(char *str, int i, int (*f)(int));
char			*xtgetstr(char *id, char **area);
size_t			xread(int fd, char *buff, int size);
uint8_t			split_cmd(char **to_find, t_read *term);

#endif
