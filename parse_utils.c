/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 16:08:18 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/03 14:25:43 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_cmd_path(char **env, t_arguments *arguments, char ***args)
{
	int		i;
	char	*path;

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
	arguments->cmd1_path = get_cmds_path(path, arguments->cmd1[0]);
	arguments->cmd2_path = get_cmds_path(path, arguments->cmd2[0]);
	free(path);
	if (!arguments->cmd2_path || !arguments->cmd1_path)
	{
		free_all(arguments, args, "error, wrong commands");
		return (0);
	}
	return (1);
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

int	get_args(char ***args, t_arguments *arguments)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	arguments->cmd1 = ft_calloc(array_len(args[1]) + 1, sizeof(char *));
	arguments->cmd2 = ft_calloc(array_len(args[2]) + 1, sizeof(char *));
	arguments->infile = ft_strdup(args[0][0]);
	arguments->outfile = ft_strdup(args[3][0]);
	if (args[0][1] != NULL || args[3][1] != NULL)
		return (0);
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

	//fds[1] is the fd of the infile
	//fds[0] is the fd of output file
int	check_args(t_arguments *arguments)
{
	arguments->fds = ft_calloc(sizeof(int), 2);
	if (!arguments->fds)
		return (0);
	arguments->fds[0] = open(arguments->outfile, O_WRONLY | O_CREAT, 0644);
	arguments->fds[1] = open(arguments->infile, O_RDONLY);
	if (arguments->fds[0] < 0 || arguments->fds[1] < 0)
		return (0);
	return (1);
}

void	parse_args(char ***args, char *argv[], int *i, t_arguments *arguments)
{
	while (argv[*i])
	{
		args[*i - 1] = ft_split(argv[*i], ' ');
		if (!args[*i - 1])
			free_all(arguments, args, "ft_split");
		(*i)++;
	}
	args[*i - 1] = 0;
}
