#ifndef EXPANSION_H
# define EXPANSION_H

# include "sh42.h"

/*
**  EXPANSION
*/

void 		add_assign_env(t_lst *lst, t_core *shell);

uint8_t		expansion(t_core *shell, t_process *process);
char 		*exp_math(char *data, t_core *shell);
char 		*exp_cmd_subs(char *data, t_core *shell);
char 		*exp_param(char *data, t_core *shell);
char 		*exp_tilde(char *data, t_core *shell);
char 		*exp_error(char *data, t_core *shell);
char 		*cmd_substitution_expansion(char *data, t_core *shell);
uint8_t 	is_expansion(e_pstate id);

#endif