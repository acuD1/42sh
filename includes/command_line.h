/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_line.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/04 14:09:42 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/06 21:23:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef COMMAND_LINE_H
# define COMMAND_LINE_H

/*
**		Configuration
*/

int8_t		init_termcaps(t_read *term);
void		init_cmd_line(t_core *shell, t_read *term);
int8_t		init_config(t_core *shell);
int8_t		reset_config(t_core *shell);
int8_t		get_size(t_read *term);

/*
**		Prompt/Subprompt
*/

int8_t		init_prompt(t_core *shell);
void		display_prompt(t_read *term);
void		display_subprompt(t_read *term);
void		goto_prompt(t_read *term);
void		get_prompt_value(t_core *shell, char *key);

/*
**		Check Caps and Interpret
*/

u_int8_t	check_caps(char *buf, t_read *term);
void		insert_in_buffer(char *buf, t_read *term);
void		insert_char_in_buffer(char buf, t_read *term, int buf_index);
void		insert_str_in_buffer(char *d_name, t_read *term);

/*
**		Cursor Motion
*/

void		move_right(char *buf, t_read *term);
void		move_left(char *buf, t_read *term);
void		move_key_up(t_read *term);
void		move_key_down(t_read *term);
void		jump_words(char *buf, t_read *term, uint64_t value);

/*
**		Delete Keys
*/

void		del_key(t_read *term);
void		bs_key(char *buf, t_read *term);
void		clr_screen(t_read *term);

/*
**		History
*/

int8_t		init_history(t_read *term);
int8_t		write_history(t_read *term);
void		save_history(t_read *term);
void		research_mode(t_read *term);
void		check_expansions(t_read *term);
void		insert_content(int j, int i, t_read *term, char *content);
int64_t		call_number(t_read *term, int i);
int64_t		callback_number(t_read *term, int i);
int64_t		call_word(t_read *term, int i);
int64_t		last_cmd_back(t_read *term, int i);

/*
**		Subprompt/Multiline
*/

u_int8_t	check_subprompt(t_core *shell);
u_int8_t	check_backslash(t_read *term, char *quote);
u_int8_t	charset_count(t_read *term, char charset, int i);
u_int8_t	quotes_is_matching(t_read *term, char *quote);
u_int8_t	read_multiline(t_read *term, char sb);
void		load_subprompt(char quote, t_read *term);
char		*load_heredoc(t_core *shell, char *key);

/*
**		Auto completion
*/

void		auto_complete_mode(t_read *term);
void		read_directories(char *to_find, t_read *term);
void		to_complete_bin(char *to_find, t_read *term);
void		to_complete_buffer(char *to_find, t_read *term);
void		display_current_directory(t_read *term, char *dir);
void		delete_last_cmd(char *d_name, t_read *term);
void		parse_env(char **prev_b, char *to_find, t_read *term);
char		**split_path(t_core *shell, char *str);
uint8_t		read_again(char **prev_b, char *path, char *name, t_read *term);

/*
**		Utils/Tools
*/

int			my_outc(int c);
u_int8_t	get_width_last_line(t_read *term);
u_int8_t	get_width_current_line(t_read *term);
u_int64_t	get_mask(char *buff);
int			is_dot(char *d_name);
u_int8_t	is_tab(char *d_name, t_read *term);
u_int8_t	is_dir(char *dir);
u_int8_t	split_cmd(char **to_find, t_read *term);

/*
**		Functions safe
*/

void		xtputs(char *str, int i, int (*f)(int));
char		*xtgetstr(char *id, char **area);
size_t		xread(int fd, char *buff, int size);

#endif
