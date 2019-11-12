#include "sh42.h"

// static char	*read_subcmd_file(int fd)
// {
// 	char		buffer[4097];
// 	char		*output;
// 	char		*prev;
// 	ssize_t		len;

// 	output = NULL;
// 	while ((len = read(fd, buffer, 4096)) > 0)
// 	{
// 		buffer[len] = '\0';
// 		prev = output;
// 		output = ft_strjoinf(prev, buffer, 1);
// 	}
// 	if (output == NULL)
// 		return (NULL);
// 	len = ft_strlen(output);
// 	while (len > 0 && output[--len] == '\n')
// 		output[len] = '\0';
// 	return (output);
// }

// static char	*fork_subcmd(char *tempfile_path, char *cmd)
// {
// 	char	*value;
// 	pid_t	child;
// 	int		fd;

// 	value = NULL;
// 	if ((child = fork()) == 0)
// 	{
// 		fd = open(tempfile_path, O_CREAT | O_WRONLY, 0600);
// 		if (fd == -1)
// 			exit(1);
// 		dup2(fd, STDOUT_FILENO);
// 		close(fd);
// 		return (cmd);
// 	}
// 	else if (child > 0)
// 	{
// 		fd = open(tempfile_path, O_RDONLY);
// 		if (fd == -1)
// 			return (NULL);
// 		value = read_subcmd_file(fd);
// 		close(fd);
// 	}
// 	return (value);
// }

// char		*subcmd_exec(char *cmd)
// {
// 	char	*tempfile_path;
// 	char	*value;

// 	tempfile_path = ft_strdup("~/.cmds_subs");
// 	// tempfile_path = get_tempfile_path(".cmds_subs");
// 	if (tempfile_path == NULL)
// 		return (NULL);
// 	value = fork_subcmd(tempfile_path, cmd);
// 	// unlink(tempfile_path);
// 	free(tempfile_path);
// 	return (value);
// }

char *cmd_substitution_expansion(t_token *token, t_core *shell)
{
	t_lst *lst_job;
	// t_lst *tmp_lst;
	char *str;
	char *ret;
	int i;

	ret =  NULL;
	lst_job = NULL;
	i = ft_strlen(token->data);
	str = ft_strsub(token->data, 2, i - 3);
	// ret = subcmd_exec(str);
	(void)shell;
	// lst_job = lexer_parser_analyzer(shell, str);
	// tmp_lst = shell->job_list;
	// shell->job_list = lst_job;
	// exec_from_shell_job_list(lst_job, shell);
	// if (lst_job && ((t_job*)lst_job->content)->command)
		// printf("%s\n", ((t_job*)lst_job->conddtent)->command);
	return (ret);
}
