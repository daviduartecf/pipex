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

void	data_init(t_arguments **arguments, char ****args, int argc)
{
	*arguments = ft_calloc(sizeof(t_arguments), 1);
	if (!*arguments)
	{
		perror("ft_calloc");
		exit(1);
	}
	*args = malloc(sizeof(char **) * argc);
	if (!*args)
	{
		perror("malloc");
		free(arguments);
		exit(1);
	}
}

void	parse_args(char ***args, char *argv[], int *i, t_arguments *arguments)
{
	while (argv[*i])
	{
		args[*i - 1] = ft_split(argv[*i], ' ');
		if (!args[*i - 1])
			free_all(arguments, *args, (*i - 1), "ft_split");
		(*i) ++;
	}
	args[*i - 1] = 0;
}

int	main(int argc, char *argv[])
{
	t_arguments	*arguments;
	char ***args;
	int		*fds, *pipefd;
	int		i, pid1, pid2;
	char	*path;

	i = 1;
	if (argc != 5)
	{
		ft_printf("Correct use: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		return (1);
	}
	data_init(&arguments, &args, argc);
	parse_args(args, argv, &i, arguments);
	if (!get_args(args, arguments))
		free_all(arguments, *args, i - 1, "get_args");
	fds = check_args(arguments);
	if (!fds)
		free_all(arguments, *args, i - 1, "error opening files");
	pipefd = ft_calloc(sizeof(int), 2);
	if (pipe(pipefd) == -1)
		free_all(arguments, *args, i - 1, "error pipe");
	path = get_path(environ);
	arguments->cmd1_path = get_cmd_path(path, arguments->cmd1[0]);
	arguments->cmd2_path = get_cmd_path(path, arguments->cmd2[0]);
	printf("cmd path: %s\n", arguments->cmd1_path);
	printf("cmd path: %s\n", arguments->cmd2_path);
	pid1 = fork();
	if (pid1 < 0)
		free_all(arguments, *args, i - 1, "error fork");
	//child to do the first command
	if (pid1 == 0)
	{
		printf("CHILD1: Completed\n");
		dup2(fds[1], STDIN_FILENO);
		close(fds[1]);
		close(fds[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		execve(arguments->cmd1_path, arguments->cmd1, NULL);
		perror("execvp command1");
		exit(EXIT_FAILURE);
	}
	pid2 = fork();
	if (pid2 < 0)
		free_all(arguments, *args, i - 1, "error fork");
	//child to do the second command
	//write in the outfile
	if (pid2 == 0)
	{
		printf("CHILD2: Completed\n");
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[1]);
		close(pipefd[0]);
		dup2(fds[0], STDOUT_FILENO);
		close(fds[1]);
		close(fds[0]);
		execve(arguments->cmd2_path, arguments->cmd2, NULL);
		perror("execvp command2");
		exit(EXIT_FAILURE);
	}
	close(pipefd[0]);
	close(pipefd[1]);
	close(fds[1]);
	close(fds[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
	free_arguments(arguments);
	free_args(args, i - 1);
	free(pipefd);
	free(fds);
	free(path);
	printf("PARENT: Completed\n");
	return 0;
}
