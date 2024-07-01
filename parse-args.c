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

	arguments->cmd1 = ft_calloc(array_len(args[1]) + 1, sizeof(char *));
	arguments->cmd2 = ft_calloc(array_len(args[2]) + 1, sizeof(char *));
	arguments->infile = ft_strdup(args[0][0]);
	arguments->outfile = ft_strdup(args[3][0]);

	while (args[1][j])
	{
		arguments->cmd1[j] = ft_strdup(args[1][j]);
		j ++;
	}
	while (args[2][i])
	{
		arguments->cmd2[i] = ft_strdup(args[2][i]);
		i ++;
	}
	return (1);
}

int	*check_args(t_arguments *arguments)
{
	int	*fds;

	fds = ft_calloc(sizeof(int), 2);
	if (!fds)
		return (NULL);
	//fds[1] is the fd of the infile
	//fds[0] is the fd of output file
	fds[0] = open(arguments->outfile, O_WRONLY | O_CREAT, 0644);
	fds[1] = open(arguments->infile, O_RDONLY);
	if (fds[0] < 0 || fds[1] < 0)
		return (NULL);

	return (fds);
}

char	*get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
			return (ft_strdup(env[i] + 5));
		i ++;
	}
	return (NULL);
}

char	*get_cmd_path(char	*path, char	*cmd)
{
	int	i;
	char	*full_path;
	char	**directory;
	char	*true_cmd;

	i = 0;
	true_cmd = ft_strjoin("/", cmd);
	directory = ft_split(path, ':');
	if (!directory)
		return (NULL);
	while (directory[i])
	{
		full_path = ft_strjoin(directory[i], true_cmd);
		if (access(full_path, X_OK) == 0)
		{
			free(true_cmd);
			free_array(directory);
			return (full_path);
		}
		free(full_path);
		i ++;
	}
	return (NULL);
}

int	main(int argc, char *argv[])
{
	t_arguments	*arguments;
	char ***args;
	int		*fds, *pipefd;
	int		i, pid1, pid2;
	char	*path;

	if (argc != 5)
	{
		ft_printf("Correct use: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		return (1);
	}
	arguments = ft_calloc(sizeof(t_arguments), 1);
	if (!arguments)
	{
		perror("ft_calloc");
		return (1);
	}
	args = malloc(sizeof(char **) * (4 + 1));
	if (!args)
	{
		perror("malloc");
		free(arguments);
		return 1;
	}
	i = 1;
	while (argv[i])
	{
		args[i - 1] = ft_split(argv[i], ' ');
		if (!args[i - 1])
			free_all(arguments, *args, i - 1, "ft_split");
		i ++;
	}
	args[i - 1] = 0;
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
