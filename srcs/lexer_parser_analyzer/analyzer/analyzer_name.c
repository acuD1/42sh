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

char **fill_cmd_job(char *str, t_job *job)
{
	if (!job->process.av)
	{
		if (!(job->process.av = (char**)malloc(sizeof(char*) + 1)))
			return (NULL);
		job->process.av[0] = ft_strdup(str);
		job->process.av[1] = NULL;
	}
	return (job->process.av);
}

char **ft_add_arg_cmd_job(char **tablo, char *str)
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

void cmd_analyze(t_analyzer *analyzer)
{
	// ft_printf("WOWOWORD   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	// ft_printf("CMD state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	if (analyzer->state == A_START)
		analyzer->process.av = fill_cmd_job(((t_token*)analyzer->lexer->tok->content)->data, &analyzer->job);
	else if (analyzer->state == A_WORD)
	{
		analyzer->process.av = ft_add_arg_cmd_job(analyzer->job.process.av, ((t_token*)analyzer->lexer->tok->content)->data);
		//Va y avoir du leak je sais pas comment ce comporte les char** alloué dans une stack
	}
	else if (analyzer->state == A_REDIRECT)
	{
		analyzer->redir.op[1] = ft_strdup(((t_token*)analyzer->lexer->tok->content)->data);
		redir_analyze(analyzer);
	}
	if (analyzer->lexer->tok->next && (((t_token*)analyzer->lexer->tok->next->content)->id == 24))
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
	if (((t_token*)analyzer->lexer->tok->content)->id == 0)
	{
		// analyzer->job.command = getjoblistcmdtab(analyzer->job.process_list);
		// ft_printf("strp %s\n", analyzer->job.command);
		job_analyze(analyzer);
		return;
	}
	else
		analyzer->state = A_STOP;
	//NE PASSERA PEUT ETRE PAS DEDANS CF P_END DU LEXER
	// doit en theorie etre le dernier token de a list et free la list si la list de jobs est OK
}
