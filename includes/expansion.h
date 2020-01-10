/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcatusse <fcatusse@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/30 18:43:16 by fcatusse          #+#    #+#             */
/*   Updated: 2019/11/30 18:43:17 by fcatusse         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANSION_H
# define EXPANSION_H

# include "sh42.h"

/*
**  EXPANSION
*/

e_pstate find_expansion(char *str);
int8_t		add_assign_env(t_lst *lst, t_core *shell);

void		expansion(t_core *shell, t_process *process);
char 		*exp_math(t_token* tok, t_core *shell, t_expansion *exp);
char 		*no_exp(t_token* tok, t_core *shell, t_expansion *exp);
char 		*exp_cmd_subs(t_token* tok, t_core *shell, t_expansion *exp);
char 		*exp_param(t_token* tok, t_core *shell, t_expansion *exp);
char 		*exp_tilde(t_token* tok, t_core *shell, t_expansion *exp);
char 		*exp_error(t_token* tok, t_core *shell, t_expansion *exp);
char 		*cmd_substitution_expansion(t_token* tok, t_core *shell, t_expansion *exp);
char *exp_dbquote(t_token *tok, t_core *shell, t_expansion *exp);
uint8_t 	is_expansion(e_pstate id);
int8_t		get_index_expan(char *str, int index);

#endif