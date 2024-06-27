#include "pipex.h"

int	array_len(char **str_array)
{
	int	len;

	len = 0;
	while (str_array[len])
	{
		len ++;
	}
	return (len);
}

int	get_args(char ***args, t_arguments *arguments)
{
	int i = 0;
	int j = 0;
	int	len1 = array_len(args[1]);
	int	len2 = array_len(args[2]);

	arguments->cmd1 = ft_calloc(sizeof(char *), len1 + 1);
	arguments->cmd2 = ft_calloc(sizeof(char *), len2 + 1);

	arguments->infile = *args[0];
	arguments->outfile = *args[3];

	while (args[1][j])
	{
		arguments->cmd1[j] = args[1][j];
		j ++;
	}
	while (args[2][i])
	{
		arguments->cmd2[i] = args[2][i];
		i ++;
	}
	return (1);
}

int	*check_args(t_arguments *arguments)
{
	int	*fds;

	fds = ft_calloc(sizeof(int), 2);
	//fds[1] is the fd of the infile
	//fds[0] is the fd of output file
	fds[0] = open(arguments->outfile, O_WRONLY | O_CREAT, 0644);
	fds[1] = open(arguments->infile, O_RDONLY);
	if (fds[0] < 0 || fds[1] < 0)
		return (NULL);

	return (fds);
}

int	main(int argc, char *argv[])
{
	t_arguments	*arguments;
	char ***args;
	int		*fds, *pipefd;
	int		i, pid1, pid2;

	arguments = ft_calloc(sizeof(t_arguments), 1);
	i = 1;
	if (argc == 5)
	{
		args = malloc(sizeof(char **) * 4);
		if (!args)
			return (1);
		while (argv[i])
		{
			args[i - 1] = ft_split(argv[i], ' ');
			i ++;
		}
		args[i - 1] = 0;
	}
	else
	{
		printf("Correct use: ./pipex infile \"cmd1\" \"cmd2\" outfile");
		return (0);
	}
	if (!get_args(args, arguments))
		exit(1);
	fds = check_args(arguments);
	pipefd = ft_calloc(sizeof(int), 2);
	//pipefd[0] = fds[0];
	//pipefd[1] = fds[1];
	if (!fds)
		exit(1);
	if (pipe(pipefd) == -1)
		return (1);

	pid1 = fork();
	if (pid1 < 0)
		return (2);
	if (pid1 == 0)
	{
		printf("CHILD1: Completed\n");
		dup2(fds[1], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execve("/usr/bin/cat", arguments->cmd1, NULL);
		perror("execvp cat");
		exit(EXIT_FAILURE);
	}

	pid2 = fork();
	if (pid2 < 0)
		return (2);
	if (pid2 == 0)
	{
		printf("CHILD2: Completed\n");
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		dup2(fds[0], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
		execve("/usr/bin/wc", arguments->cmd2, NULL);
		perror("execvp wc");
		exit(EXIT_FAILURE);
	}

	close(pipefd[0]);
	close(pipefd[1]);
	close(fds[1]);
	close(fds[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	printf("PARENT: Completed\n");
	return 0;
}
