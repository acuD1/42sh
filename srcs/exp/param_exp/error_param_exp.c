char		*check_env_key(char *key, t_core *shell)
{
	t_db *db;

	db = search_db(shell->env, key);
	if (db)
		return (db->value);
	return (NULL);
}


char *questionmark_format(char **tablo, t_core *shell)
{
	char *value;
	char *word;

	word = NULL;
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	ft_dprintf(STDERR_FILENO,
		"42sh: %s parameter null or not set\n", tablo[0]);
	ft_tabfree(tablo);
	return (NULL);
}

char			*length_format(char *str, t_core *shell)
{
	t_db		*db_tmp;
	
	db_tmp = NULL;
	if (ft_strchr(str, ':') || ft_strchr(str, '%') || ft_strchr(&str[1], '#'))
	{
		ft_dprintf(STDERR_FILENO, "42sh: %s : mauvaise substitution\n", str);
		return (NULL);
	}
	if ((db_tmp = search_db(shell->env, &str[1])))
	{
		ft_strdel(&str);
		return(ft_itoa(ft_strlen(db_tmp->value)));
	}
	return (ft_strdup("0"));
}

char *double_two_point_param(char **tablo, t_core *shell)
{
	int start;
	int size;
	char *tmp;
	char *value;

	start = 0;
	size = 0;
	tmp = NULL;
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		start = ft_atoi(tablo[1]);
		size = ft_atoi(tablo[2]);
		tmp = ft_strsub(value, start, size);
		ft_tabfree(tablo);
		return (tmp);
	}
	ft_tabfree(tablo);
	return (NULL);
}