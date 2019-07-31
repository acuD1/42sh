# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include "../../inc/twenty_one.h"

static int		run_fork(char *path, char **av, char **env)
{
	pid_t		pid;

	pid = fork();
	//signal(SIGINT, procesdds_signal_handler);
	if (pid == 0)
	{
		if (execve(path, av, env) == -1)
			ft_putendl_fd("Not an executable", 2);
		exit(0);
	}
	else if (pid > 0)
		wait(&pid);
	else
	{
		ft_strdel(&path);
		ft_putendl_fd("Fork failed to create process", 2);
		return (-1);
	}
	ft_strdel(&path);
	return (1);
}

char			**walking_path(char **env, char *str)
{
	char		**cmd;
	int			i;
	int			len;

	tab = NULL;
	i = -1;
	while (env && env[++i])
	{
		len = 0;
		while (env[i][len] && env[i][len] != '=')
			len++;
		if (!ft_strncmp(str, env[i], len))
		{
			cmd = ft_strsplit(env[i] + len + 1, ':');
			break ;
		}
	}
	return (cmd);
}

static int		find_builtin(char **cmd, char **env)
{
	struct stat	fd;
	char		**path;
	char		*abs_path;
	int		i;
	char		*tmp;

	i = -1;
	path = walking_path(env, "PATH");
	while (path && path[++i])
	{
		abs_path = ft_strjoin(path[i], "/");
		tmp = ft_strjoin(abs_path, cmd[0]);
		ft_strdel(&abs_path);
		abs_path = tmp;
		if (lstat(abs_path, &fd) != -1 && !(fd.st_mode & S_IFDIR))
		{
			ft_tabfree(path);
			return (run_fork(abs_path, cmd, env));
		}
		ft_strdel(&abs_path);
	}
	ft_tabfree(path);
	return (0);
}

int			exec_cmd(char **cmd, char ***env, t_read *line)
{
	struct stat	buf;

	if (check_builtins(cmd, *env, line) || find_builtin(cmd, *env))
		return (0);
	if (lstat(cmd[0], &buf) != -1)
		if (buf.st_mode & S_IXUSR)
			return (run_fork(ft_strdup(cmd[0]), cmd, *env));
	*cmd ? ft_putstr_fd(*cmd, 2) : 0;
	*cmd ? ft_putendl_fd(": Command not found.", 2) : 0;
	return (0);
}
