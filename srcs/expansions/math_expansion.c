#include "sh42.h"

char *exp_math(t_token *tok, t_core *shell, t_expansion *exp)
{
	(void)shell;
	(void)exp;
	printf("EXP_MATHS [%s]\n", tok->data);
	return (tok->data);
}
