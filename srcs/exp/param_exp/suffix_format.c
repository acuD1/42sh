#include "sh42.h"

char *smallest_suffix_param(char *value, char *pattern)
{
	int		pattern_size;

	pattern_size = ft_strlen(value) - ft_strlen(pattern);
	if (ft_strequ(value + pattern_size, pattern))
		return (ft_strsub(value, 0, pattern_size));
	return (ft_strdup(value));
}

char *largest_suffix_param(char *value, char *pattern)
{
	printf("2 suffix pattern %s value %s\n", pattern, value);
	return (NULL);
}

char		*suffix_format(char *data, t_core *shell)
{
	char *tmp;
	char *value;
	char **tablo;
	char *resultat;

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
		{
			if (tmp[0] == '%')
			{
				if (tmp[1] == '%')
					resultat = largest_suffix_param(value, tablo[1]);
				else
					resultat = smallest_suffix_param(value, tablo[1]);
			}
		}
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (resultat);
}
