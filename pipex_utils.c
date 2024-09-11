/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:15:13 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/04 16:01:23 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	data_init(t_pipex **pipex, char ****args, int argc)
{
	*pipex = ft_calloc(sizeof(t_pipex), 1);
	if (!*pipex)
	{
		perror("ft_calloc");
		exit(0);
	}
	*args = malloc(sizeof(char **) * argc);
	if (!*args)
	{
		perror("malloc");
		free(pipex);
		exit(0);
	}
}

void	close_all(t_pipex *pipex)
{
	close(pipex->pipefd[0]);
	close(pipex->pipefd[1]);
	waitpid(pipex->pid1, NULL, 0);
	waitpid(pipex->pid2, NULL, 0);
}

void	open_files(t_pipex *pipex, char ***args)
{
	if (!get_file_and_cmds(args, pipex))
		free_all(pipex, args, "error on filenames");
	pipex->pipefd = ft_calloc(sizeof(int), 2);
}
