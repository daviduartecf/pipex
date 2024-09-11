/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:27:02 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/04 15:25:11 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <errno.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/wait.h>
# include "ft_printf/includes/ft_printf.h"
# include "ft_printf/includes/libft.h"

typedef struct s_pipex
{
	int		*fds;
	pid_t	pid1;
	pid_t	pid2;
	int		*pipefd;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	char	**env_cmds;
}	t_pipex;

/* PIPEX FUNCTIONS */
void	child1_process(t_pipex *pipex, char ***args, char *envp[]);
void	child2_process(t_pipex *pipex, char ***args, char *envp[]);
void	open_files(t_pipex *pipex, char ***args);
void	close_all(t_pipex *pipex);
void	data_init(t_pipex **pipex, char ****args, int argc);
void	fork_function(t_pipex *pipex, char ***args, char *envp[]);

/* PARSING FUNCTIONS */
char	*get_cmds_path(char	*path, char	*cmd);
int		get_file_and_cmds(char ***args, t_pipex *pipex);
char	*get_cmd_path(char **env, t_pipex *pipex, char ***args, char *cmd);
void	parse_args(char ***args, char *argv[], int *i, t_pipex *pipex);

/* FREE FUNCTIONS */
void	free_args(char ***args);
void	free_array(char **array);
void	free_pipex(t_pipex *pipex);
void	last_free(t_pipex *pipex, char ***args);
void	free_all(t_pipex *pipex, char ***args, char *error);

/* UTILS */
int		array_len(char **str_array);
#endif
