#include "sh42.h"

int	ft_strnequ(char const *s1, char const *s2, size_t n)
{
	while (n-- && *s1 && *s2)
	{
		if (*s1 != *s2)
			return (0);
		s1++;
		s2++;
	}
	return (1);
}	

char *smallest_prefix_param(char *value, char *pattern)
{
	int		pattern_size;

	pattern_size = ft_strlen(pattern);
	if (ft_strnequ(value, pattern, pattern_size))
		return (ft_strsub(value, pattern_size, ft_strlen(value) - pattern_size));
	return (ft_strdup(value));
}

char *largest_prefix_param(char *value, char *pattern)
{
	printf("2 prefix pattern %s value %s\n", pattern, value);
	return (NULL);
}

char		*prefix_format(char *data, t_core *shell)
{
	char *tmp;
	char *value;
	char **tablo;
	char *resultat;

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
		{
			if (tmp[0] == '#')
			{
				if (tmp[1] == '#')
					resultat = largest_prefix_param(value, tablo[1]);
				else
					resultat = smallest_prefix_param(value, tablo[1]);
			}
		}
	}
	ft_strdel(&data);
	ft_tabfree(tablo);
	return (resultat);
}