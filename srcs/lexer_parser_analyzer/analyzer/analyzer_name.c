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

char **fill_cmd_job(char *str)
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

void cmd_analyze(t_analyzer *analyzer, t_job *job)
{
	// char *str;

	// str = NULL;
	// ft_printf("WOWOWORD   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	ft_printf("CMD state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
		(void)job;
	// if (analyzer->state == A_START)
	// {
	// 	(t_process*)(analyzer.job.process_list->content)->av = fill_cmd_job(((t_token*)analyzer->lexer->tok->content)->data);
	// 	str = ft_strjoin(((t_token*)analyzer->lexer->tok->content)->data , " ");
	// 	analyzer->job_cmd = ft_strjoinf(analyzer->job_cmd, str, 2);
	// }
	// else if (analyzer->state == A_WORD)
	// {
	// 	analyzer->process_cmd = ft_add_arg_cmd_job(analyzer->process_cmd, ((t_token*)analyzer->lexer->tok->content)->data);
	// 	//Va y avoir du leak je sais pas comment ce comporte les char** alloué dans une stack
	// }
	// else if (analyzer->state == A_REDIRECT)
	// {
	// 	analyzer->op[1] = ft_strdup(((t_token*)analyzer->lexer->tok->content)->data);
	// 	redir_analyze(analyzer);
	// }
	// if (analyzer->lexer->tok->next && (((t_token*)analyzer->lexer->tok->next->content)->id == 24))
	// 	analyzer->state = A_STOP;
	// else
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

void end_analyze(t_analyzer *analyzer, t_job *job)
{
	ft_printf("END state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->tok->content)->id ,((t_token*)analyzer->lexer->tok->content)->data);
	// if (((t_token*)analyzer->lexer->tok->content)->id == 0)
	// {
		// analyzer->job.command = getjoblistcmdtab(analyzer->job.process_list);
		// ft_printf("strp %s\n", analyzer->job.command);
		// analyzer->job_type = P_NEWLINE;
		// job_analyze(analyzer);
		(void)job;
		// return;
	// }
	// else
		analyzer->state = A_STOP;
	//NE PASSERA PEUT ETRE PAS DEDANS CF P_END DU LEXER
	// doit en theorie etre le dernier token de a list et free la list si la list de jobs est OK
}
