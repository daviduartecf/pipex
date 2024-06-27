#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	main()
{
	__pid_t pid;

	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (pid == 0)
		printf("this is the child. pid: %d\n", getpid());
	else
		printf("this is the parent. pid: %d\n", getpid());
	return 0;
}
