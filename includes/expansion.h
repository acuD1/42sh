/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:43:16 by fcatusse          #+#    #+#             */
/*   Updated: 2020/02/07 01:57:51 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

u_int8_t		is_expansion(enum e_estate id);
char			*do_expansion(t_core *shell, char *data);
void			init_expansionat(t_expansion *exp);
void			expansion_assign(t_core *shell, t_process *process);
void			expansion_redir(t_core *shell, t_process *process);
void			expansion_tok(t_core *shell, t_process *process);
char			*exp_cmd_subs(char *data, t_core *shell);
char			*no_exp(char *data, t_core *shell);
char			*exp_math(char *data, t_core *shell);
char			*exp_param(char *data, t_core *shell);
char			*exp_tilde(char *data, t_core *shell);
void			expansion(t_core *shell, t_process *process);
int				expelliarmus(char *src, int *index, char **dst, t_core *shell);
char			*exp_get_tilde(char *string, int len);
char			*exp_get_tildep(char *string, int len);
char			*exp_get_tildem(char *string, int len);
char			*exp_get_paren(char *string, int len);
char			*exp_get_bracket(char *string, int len);
char			*exp_get_dollar(char *string, int len);
char			*exp_get_dbparen(char *string, int len);
char			*exp_get_bquote(char *string, int len);
char			*exp_get_hook(char *string, int len);
enum e_estate	find_expansion(char *str);
char			*get_expansion(char *string, enum e_estate state);
char			*infinite_expansion(char *data, t_core *shell);
char			*do_exp_et_quote(t_core *shell, char *data);
int				get_word_size_ntype(int i, char *str);

#endif
