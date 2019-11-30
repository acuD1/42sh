
#include "sh42.h"

char *get_brace_param(char *str)
{
	int i;
	char *tmp;

	i = 1;
	tmp = NULL;
	while (str[++i])
	{
		if (str[i] == '}')
			break;
		i++;
	}
	if (!(tmp = ft_strsub(str, 2, i - 1)))
		return (NULL);
	return (tmp);
}

char *exp_param(char *data, t_core *shell)
{
	t_db *db_tmp;
	char *tmp;
	int i;

	i = ft_strlen(data);
	tmp = NULL;
	db_tmp = NULL;
	if (data[0] == '$' && data[1] == '{')
		tmp = get_brace_param(data);
	else if (data[0] == '$')
		tmp = ft_strsub(data, 1, i - 1);
	// if (tmp[0] == '?')
		// return(get_job_return(shell));
	if (!(db_tmp = search_db(shell->env, tmp)))
	{
		free(tmp);
		free(data);
		return (ft_strdup(""));
	}
	else
	{
		free(tmp);
		free(data);
		return (ft_strdup(db_tmp->value));
	}
	free(data);
	return (ft_strdup(""));
}
