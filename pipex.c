/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 11:47:13 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/04 16:02:52 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*	MAIN PROCESS */
/*		 |
	.	 |
	.	 |
	create pipe[]
	.	 |
	.  fork()
	.	 /\
	.	/  \
	.  /    \
	child1   parent
	.  |          |
	.  |        fork()
	.  |          |\
	execute       | \
	1st cmd       |  \
	.pipe[1]      |   \
	.             |    \
	.         parent    child2
	.             |          |
	.             |         execute
	.             |         2nd cmd
	.             |         pipe[0]
	.          end the
	.          program
*/

int	main(int argc, char *argv[], char *envp[])
{
	int			i;
	int			pid1;
	int			pid2;
	char		***args;
	t_pipex		*pipex;

	i = 1;
	pid1 = 0;
	pid2 = 0;
	if (argc != 5)
	{
		ft_printf("Correct use: ./pipex infile \"cmd1\" \"cmd2\" outfile\n");
		return (1);
	}
	data_init(&pipex, &args, argc);
	parse_args(args, argv, &i, pipex);
	open_files(pipex, args);
	if (pipe(pipex->pipefd) == -1)
		free_all(pipex, args, "error pipe");
	fork_function(pipex, args, envp);
	close_all(pipex);
	last_free(pipex, args);
	return (0);
}

void	child1_process(t_pipex *pipex, char ***args, char *envp[])
{
	char	*path;

	pipex->fds = ft_calloc(sizeof(int), 2);
	if (!pipex->fds)
		return ;
	pipex->fds[1] = open(pipex->infile, O_RDONLY);
	if (pipex->fds[1] < 0)
		free_all(pipex, args, "error opening/writing files");
	path = get_cmd_path(envp, pipex, args, pipex->cmd1[0]);
	dup2(pipex->fds[1], STDIN_FILENO);
	close(pipex->fds[1]);
	dup2(pipex->pipefd[1], STDOUT_FILENO);
	close(pipex->pipefd[1]);
	close(pipex->pipefd[0]);
	if (execve(path, pipex->cmd1, envp) == -1)
	{
		perror("execvp command1");
		exit(0);
	}
}

void	child2_process(t_pipex *pipex, char ***args, char *envp[])
{
	char	*path;

	pipex->fds = ft_calloc(sizeof(int), 2);
	if (!pipex->fds)
		return ;
	pipex->fds[0] = open(pipex->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (pipex->fds[0] < 0)
		free_all(pipex, args, "error opening/writing files");
	path = get_cmd_path(envp, pipex, args, pipex->cmd2[0]);
	dup2(pipex->pipefd[0], STDIN_FILENO);
	close(pipex->pipefd[1]);
	close(pipex->pipefd[0]);
	dup2(pipex->fds[0], STDOUT_FILENO);
	close(pipex->fds[0]);
	free(pipex->fds);
	if (execve(path, pipex->cmd2, envp) == -1)
	{
		perror("execvp command2");
		exit(0);
	}
}

void	fork_function(t_pipex *pipex, char ***args, char *envp[])
{
	pipex->pid1 = fork();
	if (pipex->pid1 < 0)
		free_all(pipex, args, "error fork");
	if (pipex->pid1 == 0)
		child1_process(pipex, args, envp);
	pipex->pid2 = fork();
	if (pipex->pid2 < 0)
		free_all(pipex, args, "error fork");
	if (pipex->pid2 == 0)
		child2_process(pipex, args, envp);
}
