/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 15:17:27 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/01 15:51:28 by daduarte         ###   ########.fr       */
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

void	free_arguments(t_arguments *arguments)
{
	int	i;

	i = 0;
	free_array(arguments->cmd1);
	free_array(arguments->cmd2);
	free(arguments->cmd1_path);
	free(arguments->cmd2_path);
	free(arguments->infile);
	free(arguments->outfile);
	free(arguments);
}

void	free_args(char ***args, int	len)
{
	int	i;
	int	j;

	i = 0;
	if (args)
	{
		while (i < len)
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

void	free_all(t_arguments *arguments, char **args, int len, char *error)
{
	int	i;

	i = 0;
	perror(error);
	while (i < len)
		free(args[i]);
	free(args);
	if (error[0] == 'e')
		free_arguments(arguments);
	free(arguments->cmd1_path);
	free(arguments->cmd2_path);
	free(arguments);
	exit(1);
}
