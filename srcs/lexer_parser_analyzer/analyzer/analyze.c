#include "sh42.h"

// int ft_tablen(char **tb)
// {
// 	int i;

// 	i = 0;
// 	if (!tb)
// 		return (0);
// 	while (tb[i])
// 		i++;
// 	return (i);
// }

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

void cmd_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_core *shell)
{
	// ft_printf("WOWOWORD   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	if (!job->cmd)
		job->cmd = fill_cmd_job(((t_token*)lexer->tok->content)->data, job);
	else if (analyzer->state == A_WORD)
		job->cmd = ft_add_arg_cmd_job(job->cmd, ((t_token*)lexer->tok->content)->data);
	if (analyzer->state == A_REDIRECT)
		job->redir->op[1] = ft_strdup(((t_token*)lexer->tok->content)->data);
	analyzer->state = A_WORD;
	(void)shell;
	//check les prochain token pour savoir si ils sont conforme a la grammaire
	// TANT QUE token word 
	// premier token word  = cmd 
	// le suivant = opt 
	// le reste = cmd data
}

void end_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_core *shell)
{
	ft_printf("ENNNNNND   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	analyzer->state = A_STOP;
	(void)job;
	(void)shell;

	//NE PASSERA PEUT ETRE PAS DEDANS CF P_END DU LEXER
	// doit en theorie etre le dernier token de a list et free la list si la list de jobs est OK
}	

t_job *fetch_job(t_job *job)
{
	t_job	*job_data;

	job_data = job;
	return (job_data);
}

void separator_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_core *shell)
{
	// ft_printf("SEPARARARTOR   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	// analyzer->state = A_SEPARATOR;
	(void)job;
	if (analyzer->state == A_WORD)
	{
		ft_lstappend(&shell->jobs, ft_lstnew(fetch_job(job), sizeof(t_job)));
		// ft_printf("gmreangj  %s %s \n", ((t_job*)(shell->jobs->content))->cmd[0], job->redir->op[1]);
		init_job(job);
		// ft_printf("BKABKAAJ  %s %s \n", ((t_job*)(shell->jobs->content))->cmd[0], job->redir->op[1]);
		// shell->jobs = shell->jobs->next;
	}
	if (lexer->tok->next && !ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	// delimite le list de token en une list ou un job
	(void)shell;

}

void redirect_analyze(t_analyzer *analyzer, t_lexer * lexer, t_job *job, t_core *shell)
{
	// ft_printf("REDIDIDIRECT   %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)analyzer;
	(void)shell;
	(void)job;
	// job->redir->op[0] = ft_jointab(job->cmd);
	job->redir->type = ((t_token*)lexer->tok->content)->id;
	analyzer->state = A_REDIRECT;
	// analyzer->state = A_REDIRECT;
	// if (((t_token*)lexer->tok->content)->id == P_GREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_TRUNC;
	// else if (((t_token*)lexer->tok->content)->id == P_DGREAT || ((t_token*)lexer->tok->content)->id == P_ANDDGREAT)
	// 	analyzer->fd_flags = O_RDWR + O_CREAT + O_APPEND;
	// else if (((t_token*)lexer->tok->content)->id == P_LESS)
	// 	analyzer->fd_flags = O_RDONLY;
	// else if (((t_token*)lexer->tok->content)->id == P_DLESSDASH || ((t_token*)lexer->tok->content)->id == P_DLESS)
		// analyzer->state = P_HEREDOC_REDIRECT;

	// delimite une list et determine la redirection IN ou OUT ou HERE_DOC
	// met dans la struct t_filedesc l'action IN OUT HERE_DOC...
	// depuis l'actual FD vers le wanted FD
}

void error_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_core *shell)
{
	ft_printf("EROROORRR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)shell;
	(void)job;
	analyzer->state = A_ERROR;
	if (lexer->tok->next && !ft_strcmp("(null)", ((t_token*)lexer->tok->next->content)->data))
		analyzer->state = A_STOP;
	// en theorie doit devalider la list de token et la flush
}

void ionbr_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_core *shell)
{
	// ft_printf("IOOOOOOONBR  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)lexer;
	(void)shell;
	(void)job;
	(void)analyzer;
	// if (analyzer->state == A_WORD)
		// job->redir->op[0] = ft_jointab(job->cmd);
	job->redir->op[0] = ft_strdup(((t_token*)lexer->tok->content)->data);
	// job->redir->ionumber = ft_atoi(((t_token*)lexer->tok->content)->data);
	// analyzer->state = A_REDIRECT;
	// delimite la list de token en token IONBR
	// cree la struct job en consequence
	// CAD attribue l'IONBR au fd et dermine la redirection en fct de loperateur
}

void assign_analyze(t_analyzer *analyzer, t_lexer *lexer, t_job *job, t_core *shell)
{
	// ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
	(void)shell;
	(void)lexer;
	(void)job;
	analyzer->state = A_ASSIGN;

	// delimite la list de token en token ASSIGN
	// cree la struct job en consequence
	// CAD cree un token dans la list assign pour pouvoir check ensuite si les tokens word suivant correspondent a un assign
}

// void start_analyze(t_analyzer *analyzer, t_job *job, t_core *shell, t_lexer *lexer)
// {
// 	ft_printf("ASSSSSIIIIIGN  %u         %s\n", analyzer->state, ((t_token*)lexer->tok->content)->data);
// 	(void)job;
// 	analyzer->state = A_START;
// }

void init_job(t_job *job)
{
	// ft_bezro(job);
	// if (job->cmd || *job->cmd)
		// freetab(job->cmd);
	// if (!(job = (t_job*)malloc(sizeof(t_job))))
		// return;
	// job->pid = 1;
	// if (job->cmd)
		// ft_printf("%s\n", job->cmd[0]);
	job->cmd = NULL;
	job->type = A_START;
	// if (!(job->redir = (t_redir*)malloc(sizeof(t_redir))))
	// 	// return;
	// if (*job->redir->op)
	// {
		// free(job->redir->op);
		// free(job->redir->op[1]);
	// }
	job->redir->op[0] = NULL;
	job->redir->op[1] = NULL;
	job->redir->type = 0;
	// job->redir = NULL;
	// job->env = NULL;
	// job->fd->action = 0;
	// job->fd->actual = 1;
	// job->fd->wanted = 1;
	// job->status = 1;
	// job->type = A_START;
	// job->term_modes = NULL;
}

void ft_printjobcmd(t_job *job, int x)
{
	int i;
	int j;

	i = 0;
	j = 0;
	if (!job)
		return;
	else
	{
		ft_printf("JOB N: %d\n",x);
		if (job->cmd)
		{
			j = ft_tablen(job->cmd);
			ft_printf("cmd ");
			while(job->cmd[i])
			{
				ft_printf("%s ", job->cmd[i]);
				i++;
			}
			ft_printf("\n");
		}
		if (job->redir->op[0])
			ft_printf("op[0] %s\n", job->redir->op[0]);
		if (job->redir->op[1])
			ft_printf("op[1] %s\n", job->redir->op[1]);
		ft_printf("type %u \n", job->redir->type);
		// if (job->redir->ionumber)
			// ft_printf("IONUMBER %d\n", job->redir->ionumber);
	}
}

void printlstjob(t_lst *lst)
{
	t_job *tmp;
	int x;

	x = 1;
	tmp = NULL;
	if (!lst)
		return;
	while (lst)
	{
		tmp = (t_job*)lst->content;
		ft_printjobcmd(tmp, x);
		x++;
		lst = lst->next;
	}
}

	// ft_lstappend(&shell->jobs, ft_lstnew(job, sizeof(t_job)));


t_lst	*analyzer(t_core *shell)
{
	t_analyzer *analyzer;
	t_lexer *lexer;
	t_job job;

	analyzer = NULL;
	if (!shell->lexer)
		return (NULL);
	lexer = shell->lexer;
	analyzer = init_analyze(analyzer);
	init_job(&job);
	if (parser(shell, lexer) != TRUE)
	{
		//erreur
		return (shell->jobs); //shell->job = NULL;
	}
	//clean parser struct
	// while (analyzer->state != A_END)
	while (analyzer->state != A_STOP && (((t_token*)lexer->tok->next->content)->id != 24))
	{
		ft_printf("analyzer state %u || token id %u || token data %s\n", analyzer->state, ((t_token*)lexer->tok->content)->id ,((t_token*)lexer->tok->content)->data);
		analyzer->analyze[analyzer->state][((t_token*)lexer->tok->content)->id](analyzer, lexer, &job, shell);
		lexer->tok = lexer->tok->next; // faire une fct get_token qui passe au token suivant ??
	}
	// ft_lstappend(&shell->jobs, ft_lstnew(fetch_job(&job), sizeof(t_job))); // a mettre dans end et /n
	printlstjob(shell->jobs);
	//flush lexer
	return (shell->jobs);
}
