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

char *smallest_prefix_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;
	int		pattern_size;

	tablo = NULL;
	pattern_size = 0;
	tablo = ft_strsplit(data, "#");
	value = check_env_key(tablo[0], shell);
	if (!tablo[1])
	{
		ft_tabfree(tablo);
		return (ft_strdup(value));
	}
	pattern_size = ft_strlen(tablo[1]);
	if (ft_strnequ(value, tablo[1], pattern_size))
	{
		ft_tabfree(tablo);
		return (ft_strsub(value, pattern_size, ft_strlen(value) - pattern_size));
	}
	ft_tabfree(tablo);
	return (ft_strdup(value));
}

char *largest_prefix_param(char *data, t_core *shell)
{
	char *value;
	char **tablo;

	tablo = NULL;
	tablo = ft_strsplit(data, "#");
	value = check_env_key(tablo[0], shell);
	printf("2 prefix key %s value %s\n", tablo[0], value);
	return (NULL);
}

char		*prefix_format(char *data, t_core *shell)
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
				return (largest_prefix_param(data, shell));
			else
				return (smallest_prefix_param(data, shell));
		}
	}
	return (NULL);
}