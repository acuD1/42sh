/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:09:42 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/30 15:22:33 by fcatusse         ###   ########.fr       */
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
void			init_cmd_line(t_read *term, t_core *shell);
uint8_t			init_config(t_core *shell);
uint8_t			reset_config(t_core *shell, t_read *input);
int8_t			get_size(t_read *data);

/*
**		Prompt/Subprompt
*/

void			init_prompt(t_core *shell, t_read *term);
void			display_prompt(t_read *term);
void			goto_prompt(t_read *line);
void			display_subprompt(t_read *term, char *prompt);
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
void			move_in_column(uint64_t value, t_read *line);
void			jump_words(char *buf, t_read *line, uint64_t value);

/*
**		Delete Keys
*/

void			del_key(t_read *line);
void			bs_key(char *buf, t_read *line);
void			clr_screen(t_read *input);

/*
**		History
*/

int8_t			init_history(t_read *term);
void			save_history(t_read *term);
void			research_mode(t_read *line);
int8_t			write_history(t_read *line);
void			check_expansions(t_read *line);
void			call_number(t_read *line, int i);
void			last_cmd_back(t_read *line, int i);
void			callback_number(t_read *line, int i);
void			call_word(t_read *line, int i);

/*
**		Quotes and Subprompt/Multiline
*/

uint8_t			check_subprompt(t_read *line);
uint8_t			charset_count(t_read *input, char charset, int i);
uint8_t			quotes_is_matching(t_read *line, char *quote);
uint8_t			check_backslash(t_read *input, char *quote);
void			load_subprompt(char quote, t_read *line);

/*
**		Auto completion
*/

void			auto_complete_mode(char *buf, t_read *input);
void			read_directories(char *buf, char *to_find, t_read *input);
void			to_complete_bin(char *buf, char *to_find, t_read *input);
void			to_complete_buffer(char *last_buf, char *to_find, t_read *input);
void			display_current_directory(char *buf, t_read *input, char *dir);
void			delete_last_cmd(char *d_name, t_read *input);
uint8_t			is_dir(char *dir);
void			parse_env(char *prev_b, char *to_find, t_read *input);
char			**split_path(t_core *shell, char *str);
uint8_t			read_again(char **prev_b, char *path, char *name, t_read *input);

/*
**		Utils/Tools
*/

int			my_outc(int c);
uint8_t			get_width_last_line(t_read *input);
uint8_t			get_width_current_line(t_read *input);
uint64_t		get_mask(char *buff);
int			is_dot(char *d_name);
uint8_t			is_tab(char *buff, char *d_name, t_read *input);

/*
**		Functions safe
*/

void			xtputs(char *str, int i, int (*f)(int));
char			*xtgetstr(char *id, char **area);
size_t			xread(int fd, char *buff, int size);
uint8_t			split_cmd(char **last_cmd, char **to_find, t_read *input);

#endif
