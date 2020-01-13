/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: arsciand <arsciand@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:43:16 by fcatusse          #+#    #+#             */
/*   Updated: 2020/01/13 08:44:19 by arsciand         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

/*
** 	EXPANSION
*/

int8_t		add_assign_env(t_lst *lst, t_core *shell);
void		expansion(t_core *shell, t_process *process);
char		*exp_math(char *data, t_core *shell);
char		*exp_cmd_subs(char *data, t_core *shell);
char		*exp_param(char *data, t_core *shell);
char		*exp_tilde(char *data, t_core *shell);
char		*exp_error(char *data, t_core *shell);
char		*cmd_substitution_expansion(char *data, t_core *shell);
uint8_t		is_expansion(enum e_pstate id);
int8_t		get_index_expan(char *str, int index);

#endif
