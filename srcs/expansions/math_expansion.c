#include "sh42.h"

char *exp_math(char *data, t_core *shell, t_expansion *exp)
{
	(void)shell;
	(void)exp;
	printf("EXP_MATHS [%s]\n", data);
	return (data);
}
