#include "sh42.h"

int find_the_truuuth_HARRY(e_parser_state id)
{
	if (id == P_TILDEP)
		return (3);
	else if (id == P_TILDEM)
		return (2);
	else if (id == P_TILDE)
		return (1);
	else
		return (0);
}

// int getnb_exp(e_parser_state id)
// {
// 	if (id == P_DOLLAR)
// 		return (0);
// 	else if (id == P_DBPARENT)
// 		return (1);
// 	else if (id == P_PARENT)
// 		return (2);
// 	else if (id == P_BRACKET)
// 		return (3);
// 	else if (id == P_HOOK)
// 		return (4);
// 	else if (id == P_TILDE)
// 		return (5);
// 	return (6);
// }

char 	*exp_tilde(char *data, t_core *shell, t_expansion *expansion)
{
	printf("EXP_TILDE [%s %u]\n", data, expansion->type);
	t_db *db_tmp;
	char *path[] = {NULL, "HOME", "OLDPWD", "PWD"};
	int i;

	i = 0;
	db_tmp = NULL;
	if (!data && !data[0])
		return (NULL);
	// i = find_the_truuuth_HARRY(expansion->type);
	if (data[0] == '~' && data[1] && data[1] == '+')
		i = 3;
	else if (data[0] == '~' && data[1] && data[1] == '-')
		i = 2;
	else if (data[0] == '~')
		i = 1;
	if (!(db_tmp = search_db(shell->env, path[i])))
	{
		free(data);
		return (NULL);
	}
	else
	{
		printf("%s %s\n", path[i], db_tmp->value);
		free(data);
		return (data = ft_strdup(db_tmp->value));
	}
	return (NULL);
}
