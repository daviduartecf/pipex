/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:08:18 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/04 15:22:01 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*get_cmd_path(char **env, t_pipex *arg, char ***args, char *cmd)
{
	int		i;
	char	*path;
	char	*real_path;

	i = 0;
	path = NULL;
	while (env[i])
	{
		if (ft_strncmp("PATH", env[i], 4) == 0)
		{
			path = ft_strdup(env[i] + 5);
			break ;
		}
		i ++;
	}
	real_path = get_cmds_path(path, cmd);
	free(path);
	if (!real_path)
	{
		free_all(arg, args, "error: command not found");
		return (NULL);
	}
	return (real_path);
}

char	*get_cmds_path(char	*path, char	*cmd)
{
	int		i;
	char	*true_cmd;
	char	*full_path;
	char	**directory;

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
	free(true_cmd);
	free_array(directory);
	return (NULL);
}

int	get_file_and_cmds(char ***args, t_pipex *pipex)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	pipex->cmd1 = ft_calloc(array_len(args[1]) + 1, sizeof(char *));
	pipex->cmd2 = ft_calloc(array_len(args[2]) + 1, sizeof(char *));
	pipex->infile = ft_strdup(args[0][0]);
	pipex->outfile = ft_strdup(args[3][0]);
	if (args[0][1] != NULL || args[3][1] != NULL)
		return (0);
	while (args[1][j])
	{
		pipex->cmd1[j] = ft_strdup(args[1][j]);
		j ++;
	}
	while (args[2][i])
	{
		pipex->cmd2[i] = ft_strdup(args[2][i]);
		i ++;
	}
	return (1);
}

void	parse_args(char ***args, char *argv[], int *i, t_pipex *pipex)
{
	while (argv[*i])
	{
		args[*i - 1] = ft_split(argv[*i], ' ');
		if (!args[*i - 1])
			free_all(pipex, args, "ft_split");
		(*i)++;
	}
	args[*i - 1] = 0;
}
