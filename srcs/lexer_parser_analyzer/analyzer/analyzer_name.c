#include "sh42.h"

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
		free(tablo[j]);
		j++;
	}
	tb[j] = ft_strdup(str);
	tb[j + 1] = NULL;
	free(tablo);
	return (tb);
}

char *fill_cmd_job(t_analyzer *analyzer, int flag)
{
	char *str;

	str = NULL;
	if (((t_token*)analyzer->lexer->next->content)->id == 0 || !flag)
		str = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	else
		str = ft_strjoin(((t_token*)analyzer->lexer->content)->data, " ");
	analyzer->job.command = ft_strjoinf(analyzer->job.command, str, 4);
	return (analyzer->job.command);
}

void cmd_analyze(t_analyzer *analyzer)
{
	// ft_printf("CMD state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	if (analyzer->state == A_START || analyzer->state == A_SEPARATOR)
		analyzer->process.av = fill_cmd_process(((t_token*)analyzer->lexer->content)->data);
	else if (analyzer->state == A_WORD)
		analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av, ((t_token*)analyzer->lexer->content)->data);
	else if (analyzer->state == A_REDIRECT)
	{
		analyzer->redir.op[1] = ft_strdup(((t_token*)analyzer->lexer->content)->data);
		redir_analyze(analyzer);
	}
	else if (analyzer->state == A_ASSIGN)
	{
		analyzer->db.value = ft_strdup(((t_token*)analyzer->lexer->content)->data);
		ass_analyze(analyzer);
	}
	analyzer->job.command = fill_cmd_job(analyzer, 1);
	if (analyzer->lexer->next && !ft_strcmp("(null)", ((t_token*)analyzer->lexer->next->content)->data))
		analyzer->state = A_STOP;
	else if (analyzer->state == A_ASSIGN)
		analyzer->state = A_START;
	else
		analyzer->state = A_WORD;
}

void end_analyze(t_analyzer *analyzer)
{
	ft_printf("END state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->state = A_STOP;
}
