#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int	main()
{
	int	fd1;
	int	fd2;

	fd2 = open("test2.txt", O_RDONLY);
	dup2(fd2, STDIN_FILENO);
	close(fd2);

	fd1 = open("test.txt", O_WRONLY | O_CREAT, 0644);
	dup2(fd1, STDOUT_FILENO);
	close(fd1);

	char buffer[1024];
	ssize_t bytesRead;
	while ((bytesRead = read(STDIN_FILENO, buffer, sizeof(buffer))) > 0) {
		if (write(STDOUT_FILENO, buffer, bytesRead) != bytesRead) {
			perror("write");
			return 1;
		}
	}

	if (bytesRead < 0) {
		perror("read");
		return 1;
	}
	
	return (0);
}
