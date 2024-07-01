/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:08:18 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/01 16:08:56 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
