#include "sh42.h"

char 		*smallest_suffix_param(char *value, char *pattern)
{
	int		pattern_size;

	pattern_size = ft_strlen(value) - ft_strlen(pattern);
	if (ft_strequ(value + pattern_size, pattern))
		return (ft_strsub(value, 0, pattern_size));
	return (ft_strdup(value));
}

char		*suffix_format(char *data, t_core *shell)
{
	char	*tmp;
	char	*value;
	char	**tablo;
	char	*resultat;

	tmp = NULL;
	value = NULL;
	resultat = NULL;
	tablo = NULL;
	if ((tmp = ft_strchr(data, '%')))
	{
		tablo = ft_strsplit(data, "%");
		value = check_env_key(tablo[0], shell);
		if (!value || !*value)
		{
			ft_tabfree(tablo);
			return (NULL);
		}
		if (!tablo[1])
			resultat = ft_strdup(value);
		else
			resultat = smallest_suffix_param(value, tablo[1]);
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (resultat);
}


char		*smallest_prefix_param(char *value, char *pattern)
{
	int		pattern_size;

	pattern_size = ft_strlen(pattern);
	if (ft_strnequ(value, pattern, pattern_size))
		return (ft_strsub(value, pattern_size, ft_strlen(value) - pattern_size));
	return (ft_strdup(value));
}

char		*prefix_format(char *data, t_core *shell)
{
	char 	*tmp;
	char 	*value;
	char 	**tablo;
	char	*resultat;

	tmp = NULL;
	value = NULL;
	resultat = NULL;
	tablo = NULL;
	if ((tmp = ft_strchr(data, '#')))
	{
		tablo = ft_strsplit(data, "#");
		value = check_env_key(tablo[0], shell);
		if (!value || !*value)
		{
			ft_tabfree(tablo);
			return (NULL);
		}
		if (!tablo[1])
			resultat = ft_strdup(value);
		else
			resultat = smallest_prefix_param(value, tablo[1]);
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (resultat);
}