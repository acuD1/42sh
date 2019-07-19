/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdline.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 14:38:24 by fcatusse          #+#    #+#             */
/*   Updated: 2019/07/18 18:36:49 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMDLINE_H
# define CMDLINE_H

# define O_PERMISSIONS		(S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
# define O_MODE_WR		(O_CREAT | O_TRUNC | O_WRONLY)

typedef struct			s_history
{
	char			*data;
	struct s_history	*next;
	struct s_history	*prev;
}				t_history;

typedef struct			s_read
{
	char			*prompt;
	int				prompt_len;
	int				x;
	int				y;
	int				ac;
	int				width;
	int				ws_col;
	int				ws_li;
	char			buffer[4096];
	int				x_index;
	char			*line;
	struct s_history	*history;
	struct s_history	*history_index;
	struct s_read		*next;
	struct s_read		*prev;
}				t_read;

/*
** Prompt
*/
t_read	*display_prompt(t_read *term);
void	goto_prompt(t_read *line);

/*
** Cursor Moves
*/
void	move_right(char *buf, t_read *input);
void	move_left(char *buf, t_read *input);
void	move_key_up(t_read *line);
void	move_key_down(t_read *line);
void	jump_words(char *buf, t_read *line);

/*
** Delete Keys
*/
void	del_key(t_read *line);
void	bs_key(char *buf, t_read *line);

/*
** Check Caps and Interpret
*/
int	check_caps(char *buf, t_read *line);
void	insert_in_buffer(char *buf, t_read *line);
void	insert_char_in_buffer(char buf, t_read *input, int buf_index);
int	my_outc(int c);

/*
** Save history in Buffer
*/
void	save_history(t_read *term);

#endif
;
