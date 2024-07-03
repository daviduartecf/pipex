/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/03 14:15:13 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/03 14:23:51 by daduarte         ###   ########.fr       */
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

void	close_all(t_arguments *arguments, int pid1, int pid2)
{
	close(arguments->pipefd[0]);
	close(arguments->pipefd[1]);
	close(arguments->fds[1]);
	close(arguments->fds[0]);
	waitpid(pid1, NULL, 0);
	waitpid(pid2, NULL, 0);
}

void	open_files(t_arguments *arguments, char ***args)
{
	if (!get_args(args, arguments))
		free_all(arguments, args, "error on filenames");
	if (!check_args(arguments))
		free_all(arguments, args, "error opening/writing files");
	arguments->pipefd = ft_calloc(sizeof(int), 2);
}
