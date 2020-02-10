/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   param_exp_opt.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guvillat <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/05 00:16:37 by guvillat          #+#    #+#             */
/*   Updated: 2020/02/05 00:16:39 by guvillat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sh42.h"

/*
*** CE FICHIER N"EST NI NORME NI LEAK_FREE NI FINIT
*/

char		*check_env_key(char *key, t_core *shell)
{
	t_db *db;

	db = search_db(shell->env, key);
	if (db)
		return (db->value);
	return (NULL);
}

char *error_moar_format_param(char **tablo, char *data)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s erreur de syntaxe dans l'expression (le symbole erroné est « %s »)\n",
		data, &data[ft_strlen(tablo[0]) + ft_strlen(tablo[1]) + ft_strlen(tablo[2]) + 2]);
	ft_tabfree(tablo);
	return (NULL);
}

char *error_moar_format_third(char **tablo, char *data)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s: %s erreur de syntaxe dans l'expression (le symbole erroné est « %s »)\n", tablo[0], data, data);
	ft_tabfree(tablo);
	return (NULL);
}

char *error_moar_format_bis(char *data)
{
	ft_dprintf(STDERR_FILENO,
		"42sh: %s erreur de syntaxe dans l'expression (le symbole erroné est « : »)\n", data);
	return (NULL);
}

int ft_strisdigit(char *str)
{
	int index;

	index = 0;
	if (str)
	{
		while (str[index])
		{
			if (ft_isdigit(str[index]))
				index++;
			else
				return (0);
		}
	}
	return (index);
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

char *dash_format(char **tablo, t_core *shell)
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
	word = check_env_key(&tablo[1][1], shell);
	ft_tabfree(tablo);
	return (ft_strdup(word));
}

char *plus_format(char **tablo, t_core *shell)
{
	char *value;
	char *word;

	word = NULL;
	value = check_env_key(tablo[0], shell);
	if (value && *value)
	{
		word = check_env_key(&tablo[1][1], shell);
		ft_tabfree(tablo);
		return (ft_strdup(word));
	}
	ft_tabfree(tablo);
	return (NULL);
}

char *egal_format(char **tablo, t_core *shell)
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
	add_assign_env(shell, tablo[0], &tablo[1][1]);
	word = ft_strdup(&tablo[1][1]);
	ft_tabfree(tablo);
	return (word);
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

char *underniercaspourlaroute(char **tablo, t_core *shell)
{
	char *value;
	char *word;

	value = check_env_key(tablo[0], shell);
	word = NULL;
	if (value && *value)
	{
		word = check_env_key(tablo[1], shell);
		if (!word || !*word)
		{
			ft_tabfree(tablo);
			return (ft_strdup(value));
		}
		else
			return (error_moar_format_third(tablo, word));
	}
	ft_tabfree(tablo);
	return (NULL);
}

char *get_two_point_param_exp(char **tablo, t_core *shell)
{
	if (tablo[1][0] == '-')
		return (dash_format(tablo, shell));
	else if (tablo[1][0] == '+')
		return (plus_format(tablo, shell));
	else if (tablo[1][0] == '=')
		return (egal_format(tablo, shell));
	else if (tablo[1][0] == '?')
		return (questionmark_format(tablo, shell));
	else
		return (underniercaspourlaroute(tablo,shell));
	ft_tabfree(tablo);
	return (NULL);
}

char		*moar_format_plz(char *data, t_core *shell)
{
	char	**tablo;
	int		tablen;

	tablo = NULL;
	tablen = 0;
	if (data[ft_strlen(data) - 1] == ':')
		return (error_moar_format_bis(data));
	if ((tablo = ft_strsplit(data, ":")))
	{
		tablen = ft_tablen(tablo);
		if (tablen > 3)
			return (error_moar_format_param(tablo, data));
		else if	(tablen == 3)
		{
			if (ft_strisdigit(tablo[1]) && ft_strisdigit(tablo[2]))
				return (double_two_point_param(tablo, shell));
		}
		else if	(tablen == 2)
			return (get_two_point_param_exp(tablo, shell));
	}
	error_format_param_exp(tablo[0]);
	ft_tabfree(tablo);
	return (NULL);
}
	
char *simple_percent_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;

	tablo = NULL;
	tablo = ft_strsplit(data, "%");
	value = check_env_key(tablo[0], shell);
	if (ft_strequ(value, tablo[1]))
		printf("%s\n", value + *tablo[1]);
	printf("1%% %s %s\n",value, tablo[0]);
	return (NULL);
}

char *double_percent_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;

	tablo = NULL;
	tablo = ft_strsplit(data, "%");
	value = check_env_key(tablo[0], shell);
	printf("2%% %s %s\n",value, tablo[0]);
	return (NULL);
}

char *simple_hashtag_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;

	tablo = NULL;
	tablo = ft_strsplit(data, "#");
	value = check_env_key(tablo[0], shell);
	printf("2## %s %s\n",value, tablo[0]);
	return (NULL);
}

char *double_hashtag_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;

	tablo = NULL;
	tablo = ft_strsplit(data, "#");
	value = check_env_key(tablo[0], shell);
	printf("1# %s %s\n",value, tablo[0]);
	return (NULL);
}



char		*percent_format(char *data, t_core *shell)
{
	//	x=file.c
	//	affiche du debut jusquau pattern si ca match sinn affiche tout
		//	echo ${x%.c} => file
			//	garde le plus petit pattern qui a match
		//	echo ${x%%.c} => file
			//	garde le plus grand pattern qui a match
	char *tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(data, '%')))
	{
		if (tmp[0] == '%')
		{
			if (tmp[1] == '%')
				return (double_percent_param(data, shell));
			else
				return (simple_percent_param(data, shell));
		}
	}
	return (NULL);
}

char		*hashtag_format(char *data, t_core *shell)
{
	//	x=file.c
	//	affiche du pattern jusqua la fin si ca match sinn affiche tout
		//	echo ${x#file} => .c  
			//	garde le plus petit pattern qui a match
		//	echo ${x##fil} => e.c
			//	garde le plus grand pattern qui a match
	char *tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(data, '#')))
	{
		if (tmp[0] == '#')
		{
			if (tmp[1] == '#')
				return (double_hashtag_param(data, shell));
			else
				return (simple_hashtag_param(data, shell));
		}
	}
	return (NULL);
}