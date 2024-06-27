#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int	main(int argc, char *argv[])
{
	char *command[3];
	command[0] = "ls";
	command[1] = "-l";
	command[2] = NULL;
	char *command2[3];
	command2[0] = "wc";
	command2[1] = "-l";
	command2[2] = NULL;
	int	fd[2];
	if (pipe(fd) == -1)
		return (1);

	int	pid1 = fork();
	if (pid1 < 0)
		return (2);
	printf("FDS\n");
	// Get the ls

	int	pid2 = fork();
	if (pid2 < 0)
		return (3);
	printf("FDS2\n");
	// Get the wc
	if (pid2 == 0)
	{
		dup2(fd[0], STDIN_FILENO);
		close(fd[1]);
		close(fd[0]);
		execve("/usr/bin/wc", command2, NULL);
	}
	close(fd[1]);
	close(fd[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("PARENT\n");
	return 0;
}
