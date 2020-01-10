
#include "sh42.h"

char *get_brace_param(char *str)
{
	int i;
	char *tmp;

	i = 0;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '}')
			break;
	}
	if (!(tmp = ft_strsub(str, 2, i - 2)))
		return (NULL);
	return (tmp);
}

char *exp_param(t_token *tok, t_core *shell, t_expansion *exp)
{
	t_db *db_tmp;
	char *tmp;
	int i;

	i = ft_strlen(tok->data);
	tmp = NULL;
	db_tmp = NULL;
	if (tok->data[0] == '$' && tok->data[1] == '{')
		tmp = get_brace_param(tok->data);
	else if (tok->data[0] == '$')
		tmp = ft_strsub(tok->data, 1, i - 1);
	if ((db_tmp = search_db(shell->env, tmp)))
	{
		free(tmp);
		return (ft_strdup(db_tmp->value));
	}
	free(tmp);
	(void)exp;
	return (NULL);
}
