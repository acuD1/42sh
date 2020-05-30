#include <signal.h>
#include <stdio.h>

void	sighdl(int signum)
{
	dprintf(2, "SIG = %d\n", signum);
}

int		main()
{
	signal(SIGHUP, sighdl);
	signal(SIGQUIT, sighdl);
	signal(SIGTERM, sighdl);
	while (1) ;
}
