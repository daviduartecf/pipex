/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:47:13 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/03 14:14:53 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	int			i;
	int			pid1;
	int			pid2;
	char		***args;
	t_arguments	*arguments;

	i = 1;
	pid1 = 0;
	pid2 = 0;
	if (argc != 5)
	{
		ft_printf("Correct use: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		return (1);
	}
	data_init(&arguments, &args, argc);
	parse_args(args, argv, &i, arguments);
	open_files(arguments, args);
	if (pipe(arguments->pipefd) == -1)
		free_all(arguments, args, "error pipe");
	get_cmd_path(envp, arguments, args);
	fork_function(arguments, args, pid1, pid2);
	close_all(arguments, pid1, pid2);
	last_free(arguments, args);
	return (0);
}

void	child_process(t_arguments *arguments, int child)
{
	if (child == 1)
	{
		dup2(arguments->fds[1], STDIN_FILENO);
		close(arguments->fds[1]);
		close(arguments->fds[0]);
		dup2(arguments->pipefd[1], STDOUT_FILENO);
		close(arguments->pipefd[1]);
		close(arguments->pipefd[0]);
		execve(arguments->cmd1_path, arguments->cmd1, NULL);
		perror("execvp command1");
		exit(EXIT_FAILURE);
	}
	else if (child == 2)
	{
		dup2(arguments->pipefd[0], STDIN_FILENO);
		close(arguments->pipefd[1]);
		close(arguments->pipefd[0]);
		dup2(arguments->fds[0], STDOUT_FILENO);
		close(arguments->fds[1]);
		close(arguments->fds[0]);
		execve(arguments->cmd2_path, arguments->cmd2, NULL);
		perror("execvp command2");
		exit(EXIT_FAILURE);
	}
}

void	fork_function(t_arguments *arguments, char ***args, int pid1, int pid2)
{
	pid1 = fork();
	if (pid1 < 0)
		free_all(arguments, args, "error fork");
	if (pid1 == 0)
		child_process(arguments, 1);
	pid2 = fork();
	if (pid2 < 0)
		free_all(arguments, args, "error fork");
	if (pid2 == 0)
		child_process(arguments, 2);
}
