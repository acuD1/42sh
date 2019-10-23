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
	if (!job->cmd)
	{
		if (!(job->cmd = (char**)malloc(sizeof(char*) + 1)))
			return (NULL);
		job->cmd[0] = ft_strdup(str);
		job->cmd[1] = NULL;
	}
	return (job->cmd);
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
		free(tablo[j]);
		j++;
	}
	tb[j] = ft_strdup(str);
	tb[j + 1] = NULL;
	free(tablo);
	return (tb);
}

t_lst *cmd_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_lst *lst)
{
	// ft_printf("WOWOWORD   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	ft_printf("state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)lexer->tok->content)->id ,((t_token*)lexer->tok->content)->data);
	if (((t_token*)lexer->tok->content)->id == 21)
	{
		if (analyzer->state == A_START) // && !job->cmd)
			job->cmd = fill_cmd_job(((t_token*)lexer->tok->content)->data, job);
		else if (analyzer->state == A_WORD)
			job->cmd = ft_add_arg_cmd_job(job->cmd, ((t_token*)lexer->tok->content)->data);
		printf("{%s}\n", job->cmd[0]);
	}
	else if (((t_token*)lexer->tok->next->content)->id == 0)
	{
		ft_lstappend(&lst, ft_lstnew(fetch_job(job), sizeof(t_job)));
		job = init_job();
	}
	// if (analyzer->state == A_REDIRECT)
		// job->redir->op[1] = ft_strdup(((t_token*)lexer->tok->content)->data);
	analyzer->state = A_WORD;
	(void)lst;
	//check les prochain token pour savoir si ils sont conforme a la grammaire
	// TANT QUE token word 
	// premier token word  = cmd 
	// le suivant = opt 
	// le reste = cmd data
	return (lst);
}

t_lst *end_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_lst *lst)
{
	ft_printf("ENNNNNND   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	analyzer->state = A_STOP;
	(void)job;
	(void)lst;
	return (lst);
	//NE PASSERA PEUT ETRE PAS DEDANS CF P_END DU LEXER
	// doit en theorie etre le dernier token de a list et free la list si la list de jobs est OK
}
