#ifndef EXPANSION_H
# define EXPANSION_H

# include "sh42.h"

/*
**  EXPANSION
*/

int8_t		add_assign_env(t_core *shell, t_process *process);

void		expansion(t_core *shell, t_process *process);
char 		*exp_math(char *data, t_core *shell);
char 		*exp_cmd_subs(char *data, t_core *shell);
char 		*exp_param(char *data, t_core *shell);
char 		*exp_tilde(char *data, t_core *shell);
char 		*exp_error(char *data, t_core *shell);
char 		*cmd_substitution_expansion(char *data, t_core *shell);
int8_t		get_index_expan(char *str, int index);

#endif
