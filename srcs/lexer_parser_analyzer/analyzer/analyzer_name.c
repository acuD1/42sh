#include "sh42.h"

char **ft_add_arg_cmd_process(char **tablo, char *str)
{
	char **tb;
	int j;

	j = 0;
	tb = NULL;
	if (!str)
		return (NULL);
	if (!tablo)
	{
		if (!(tablo = (char**)malloc(sizeof(char*) * 2)))
			return (NULL);
		tablo[0] = ft_strdup(str);
		tablo[1] = NULL;
		return (tablo);
	}
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
	// (void)flag;
	if (((t_token*)analyzer->lexer->next->content)->id == 0 || !flag)
		str = ft_strdup(((t_token*)analyzer->lexer->content)->data);
	else
		str = ft_strjoin(((t_token*)analyzer->lexer->content)->data, " ");
	analyzer->job.command = ft_strjoinf(analyzer->job.command, str, 4);
	return (analyzer->job.command);
}

t_analyzer *escape_sequence_analyzer(t_analyzer *analyzer, t_core *shell)
{
	char *str;

	str = NULL;	
	// str = ft_strdup(((t_token*)analyzer->lexer->content)->data); // dans le cas ou ya un \ tout seul mais normalement subprompt donc ca existe pas
	str = ft_strnew(0);
	while (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ && ((t_token*)analyzer->lexer->next->content)->id != P_END)
	{
		get_token(analyzer);
		(void)shell;
		if (((t_token*)analyzer->lexer->content)->id == P_SEMICOLON)
		{
			free(str);
			return (analyzer = separator_analyze(analyzer, shell));
		}
		str = ft_strjoinf(str, ((t_token*)analyzer->lexer->content)->data, 1);
		analyzer->job.command = fill_cmd_job(analyzer, 1);
	}
	free(((t_token*)analyzer->lexer->content)->data);
	((t_token*)analyzer->lexer->content)->data = ft_strdup(str);
	free(str);
	analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av, ((t_token*)analyzer->lexer->content)->data);
	((t_token*)analyzer->lexer->content)->id = P_WORD;
	return (analyzer);
}

t_analyzer *cmd_analyze(t_analyzer *analyzer, t_core *shell)
{
	// ft_dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "CMD state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	analyzer->job.command = fill_cmd_job(analyzer, 1);
	if (analyzer->state == A_REDIRECT)
	{
		analyzer->redir.op[1] = ft_strdup(((t_token*)analyzer->lexer->content)->data);
		analyzer->state = A_WORD;
		return (analyzer = redir_analyze(analyzer, shell));
	}
	else if (analyzer->state == A_ASSIGN)
	{
		analyzer->db.value = ft_strdup(((t_token*)analyzer->lexer->content)->data);
		analyzer->state = A_START;
		return (analyzer = ass_analyze(analyzer, shell));
	}
	else if (((t_token*)analyzer->lexer->content)->id == P_ESCSEQ)
		escape_sequence_analyzer(analyzer, shell);
	else
	{
		analyzer->process.av = ft_add_arg_cmd_process(analyzer->process.av, ((t_token*)analyzer->lexer->content)->data);
		if (is_expansion(((t_token*)analyzer->lexer->content)->id))
		{
			analyzer->process.type = ((t_token*)analyzer->lexer->content)->id;
			analyzer->job.type = ((t_token*)analyzer->lexer->content)->id;
		}
		analyzer->state = A_EXPANSION;
	}
	return (analyzer);
}

t_analyzer *end_analyze(t_analyzer *analyzer, t_core *shell)
{
	// ft_dprintf(getlefdpour_debug_ailleurs("/dev/ttys002"), "END state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)analyzer->lexer->content)->id ,((t_token*)analyzer->lexer->content)->data);
	separator_analyze(analyzer, shell);
	analyzer->state = A_STOP;
	return (analyzer);
}
