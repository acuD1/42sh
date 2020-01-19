srcs/builtins/bg.c:		job->notified = FALSE;
srcs/builtins/fg.c:	printf("%s\n", job->command);
srcs/builtins/jobs.c:	ptr = job->process_list;
srcs/builtins/jobs.c:		if (ptr == job->process_list)
srcs/builtins/jobs.c:			printf("[%d]%c %d %-24s %s\n", job->jobc_id, job->jobc_last
srcs/builtins/jobs.c:		printf("%d\n", job->pgid);
srcs/builtins/jobs.c:		printf("[%d]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last
srcs/builtins/jobs.c:		, (job_is_stopped(job)) ? "Stopped" : "Done", job->command);
srcs/builtins/jobs.c:			print_job(job->content, opt);
srcs/builtins/jobs.c:			job = job->next;
srcs/builtins/jobs.c:			job->content = get_job(shell->launched_jobs, process->av[i++]);
srcs/builtins/jobs.c:			print_job(job->content, opt);
srcs/exec/dispatcher.c:	process = job->process_list;
srcs/exec/dispatcher.c:		if (condition_fulfilled(shell, job->process_list, process) != SUCCESS)
srcs/exec/exec_process.c:	ptr = job->process_list;
srcs/exec/exec_process.c:		job->pgid = -1;
srcs/exec/exec_process.c:	process->pgid = job->pgid;
srcs/exec/exec_process.c:			job->pgid = process->pid;
srcs/exec/exec_process.c:		process->pgid = job->pgid;
srcs/exec/task_master.c:		ptr->next = job->next;
srcs/exec/task_master.c:		shell->job_list = job->next;
srcs/exec/task_master.c:	free_process_list(job->content);
srcs/exec/task_master.c:	ft_strdel(&(((t_job*)job->content)->command));
srcs/exec/task_master.c:	free(job->content);
srcs/exec/task_master.c:	if (!job_is_completed(job->content))
srcs/exec/task_master.c:		next = job->next;
srcs/exec/task_master.c:		launch_job(shell, job->content
srcs/exec/task_master.c:				, (((t_job*)job->content)->type != P_AND) ? TRUE : FALSE);
srcs/expansions/cmd_subs_expansion.c:// 	// if (lst_job && ((t_job*)lst_job->content)->command)
srcs/expansions/cmd_subs_expansion.c:// 		// printf("%s\n", ((t_job*)lst_job->conddtent)->command);
srcs/jobcontrol/background.c:	if (cont && kill(-job->pgid, SIGCONT) < 0)
srcs/jobcontrol/continue.c:	ptr = job->process_list;
srcs/jobcontrol/continue.c:	job->notified = FALSE;
srcs/jobcontrol/foreground.c:	if (tcsetpgrp(shell->terminal, job->pgid) != SUCCESS)
srcs/jobcontrol/foreground.c:		if (kill(-job->pgid, SIGCONT) < 0)
srcs/jobcontrol/job_utils.c:		process = ((t_job*)job->content)->process_list;
srcs/jobcontrol/job_utils.c:		job = job->next;
srcs/jobcontrol/job_utils.c:		if (((t_job*)job->content)->pgid == pgid)
srcs/jobcontrol/job_utils.c:			return (((t_job*)job->content));
srcs/jobcontrol/job_utils.c:		job = job->next;
srcs/jobcontrol/job_utils.c:	ptr = job->process_list;
srcs/jobcontrol/job_utils.c:	ptr = job->process_list;
srcs/jobcontrol/job_utils.c:	ptr = job->process_list;
srcs/jobcontrol/notifications.c:	dprintf(STDERR_FILENO, "[%i]%c  %s\t\t%s\n", job->jobc_id, job->jobc_last
srcs/jobcontrol/notifications.c:		, (job_is_stopped(job) && !job_is_completed(job)) ? "Stopped" : signal_msg(signal), job->command);
srcs/jobcontrol/notifications.c:		ptr->next = job->next;
srcs/jobcontrol/notifications.c:		shell->launched_jobs = job->next;
srcs/jobcontrol/notifications.c:	free_process_list(job->content);
srcs/jobcontrol/notifications.c:	ft_strdel(&(((t_job*)job->content)->command));
srcs/jobcontrol/notifications.c:	job->jobc_id = c + 1;
srcs/jobcontrol/notifications.c:	job->jobc_last = '+';
srcs/jobcontrol/notifications.c:		ptr = ((t_job*)job->content);
srcs/jobcontrol/notifications.c:		jnext = job->next;
srcs/lexer_parser_analyzer/analyzer/analyzer_job.c:	new->type = job->type;
srcs/lexer_parser_analyzer/analyzer/analyzer_job.c:	if (job->command)
srcs/lexer_parser_analyzer/analyzer/analyzer_job.c:		new->command = job->command;
srcs/lexer_parser_analyzer/analyzer/analyzer_job.c:	if (job->process_list)
srcs/lexer_parser_analyzer/analyzer/analyzer_job.c:		new->process_list = job->process_list;
srcs/lexer_parser_analyzer/analyzer/printanalyze.c:		ft_printjob((t_job*)job->content);
srcs/lexer_parser_analyzer/analyzer/printanalyze.c:		process = ((t_job*)job->content)->process_list;
srcs/lexer_parser_analyzer/analyzer/printanalyze.c:		job = job->next;
