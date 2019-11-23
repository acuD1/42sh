#ifndef EXPANSION_H
# define EXPANSION_H

# include "sh42.h"

/*
**  EXPANSION
*/

t_analyzer 	*expansion_analyze(t_analyzer *analyzer, t_core *shell);
uint8_t		expansion(t_core *shell, t_process *process);
char 		*exp_math(char *data, t_core *shell, t_expansion *expansion);
char 		*exp_cmd_subs(char *data, t_core *shell, t_expansion *expansion);
char 		*exp_param(char *data, t_core *shell, t_expansion *expansion);
char 		*exp_tilde(char *data, t_core *shell, t_expansion *expansion);
char 		*exp_error(char *data, t_core *shell, t_expansion *expansion);
char 		*cmd_substitution_expansion(t_token *token, t_core *shell);

void		bzero_exp_machine(t_expan machine);
void 		init_exp_machine(t_expan machine);
int 		getnb_exp(e_parser_state id);
void 		ft_free_expansion(t_expansion *exp);
void 		init_expansion(t_process *process, t_expansion *expansion);

uint8_t 	is_expansion(enum parser_state id);

#endif