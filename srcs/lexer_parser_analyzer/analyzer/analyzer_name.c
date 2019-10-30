#include "sh42.h"

char *ft_jointab(char **tablo)
{
	char *str;
	int j;
	int i;

	j = 0;
	i = ft_tablen(tablo);
	if (!(str = ft_strnew(0)) || !tablo)
		return (NULL);
	while (tablo[j] && j < i)
	{
		str = ft_strjoinf(str, tablo[j], 1);
		if (tablo[j + 1])
			str = ft_strjoinf(str, " ", 1);
		j++;
	}
	return(str);
}

char **fill_cmd_process(char *str)
{
	char **tablo;

	if (!str)
		return (NULL);
	tablo = NULL;
	if (!(tablo = (char**)malloc(sizeof(char*) + 1)))
		return (NULL);
	tablo[0] = ft_strdup(str);
	tablo[1] = NULL;
	return (tablo);
}

char **ft_add_arg_cmd_process(char **tablo, char *str)
{
	char **tb;
	int j;

	j = 0;
	tb = NULL;
	if (!str || !tablo)
		return (NULL);
	if (!(tb = (char**)malloc(sizeof(char*) * (ft_tablen(tablo) + 2))))
		return (NULL);
	while (tablo[j])
	{
		tb[j] = ft_strdup(tablo[j]);
		// free(tablo[j]);
		j++;
	}
	tb[j] = ft_strdup(str);
	tb[j + 1] = NULL;
	// free(tablo);
	return (tb);
}

char *fill_cmd_job(t_analyzer *analyzer)
{
	char *str;

	str = NULL;
	if (((t_token*)analyzer->lexer->tok->next->content)->id != 20)
		str = ft_strjoin(((t_token*)analyzer->lexer->tok->content)->data, " ");
	else
		str = ft_strdup(((t_token*)analyzer->lexer->tok->content)->data);
	((t_job*)analyzer->job_list->content)->command = ft_strjoinf(((t_job*)analyzer->job_list->content)->command, str, 1);
	free(str);
	return (((t_job*)analyzer->job_list->content)->command);
}

void cmd_analyze(t_analyzer *analyzer)
{

	// ft_printf("WOWOWORD   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	ft_printf("CMD state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	if (analyzer->state == A_START)
		analyzer->process.av = fill_cmd_process(((t_token*)analyzer->lexer->tok->content)->data);
	else if (analyzer->state == A_WORD)
		analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av, ((t_token*)analyzer->lexer->tok->content)->data);
	else if (analyzer->state == A_REDIRECT)
	{
		analyzer->redir.op[1] = ft_strdup(((t_token*)analyzer->lexer->tok->content)->data);
		redir_analyze(analyzer);
	}
	// analyzer->job.command = fill_cmd_job(analyzer);
	if (analyzer->lexer->tok->next && (((t_token*)analyzer->lexer->tok->next->content)->id == 20))
		analyzer->state = A_STOP;
	else
		analyzer->state = A_WORD;
}

char *getjoblistcmdtab(t_lst *list)
{
	t_lst *tmp;
	char *str;

	tmp = list;
	str = ft_strnew(0);
	if (!tmp)
		return (NULL);
	else
	{
		// if (tmp->next)
		printf("toto\n");
		while (tmp)
		{
			if (((t_process*)tmp->content)->av)
			{
				str = ft_jointab(((t_process*)tmp->content)->av);
				str = ft_strjoin(str, " ");
			}
			if (tmp->next)
				tmp = tmp->next;
			else
				break;
		}
		return (str);
	}
}

void end_analyze(t_analyzer *analyzer)
{
	ft_printf("END state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// if (((t_token*)analyzer->lexer->tok->content)->id == 0)
	// {
		// analyzer->job.command = getjoblistcmdtab(analyzer->job.process_list);
		// ft_printf("strp %s\n", analyzer->job.command);
		// analyzer->job_type = P_NEWLINE;
		// job_analyze(analyzer);

		// return;
	// }
	// else
		analyzer->state = A_STOP;
	//NE PASSERA PEUT ETRE PAS DEDANS CF P_END DU LEXER
	// doit en theorie etre le dernier token de a list et free la list si la list de jobs est OK
}
