#include <stdio.h>
#include <unistd.h>
#include <errno.h>

int		main(void)
{
	int ret;
	write(1, "a\n", 2);
	perror("test");
	return (212132151);
}
