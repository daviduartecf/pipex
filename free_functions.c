/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:17:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/04 16:01:06 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	free_array(char **array)
{
	int	k;

	k = 0;
	while (array[k])
	{
		free(array[k]);
		k ++;
	}
	free(array);
}

void	free_pipex(t_pipex *pipex)
{
	int	i;

	i = 0;
	free_array(pipex->cmd1);
	free_array(pipex->cmd2);
	free(pipex->infile);
	free(pipex->outfile);
	free(pipex);
}

void	free_args(char ***args)
{
	int	i;
	int	j;

	i = 0;
	if (args)
	{
		while (args[i])
		{
			j = 0;
			if (args[i])
			{
				while (args[i][j])
				{
					free(args[i][j]);
					j ++;
				}
				free(args[i]);
			}
			i ++;
		}
		free (args);
	}
}

void	free_all(t_pipex *pipex, char ***args, char *error)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free_array(args[i]);
		i++;
	}
	free(args);
	free(pipex->fds);
	free(pipex->pipefd);
	if (error[0] == 'e')
		free_pipex(pipex);
	perror(error);
	exit(0);
}

void	last_free(t_pipex *pipex, char ***args)
{
	free(pipex->pipefd);
	free_pipex(pipex);
	free_args(args);
}
