/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:27:02 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/03 14:27:39 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/includes/libft.h"

typedef struct s_arguments
{
	int		*fds;
	int		*pipefd;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
	char	**env_cmds;
	char	*cmd1_path;
	char	*cmd2_path;
}	t_arguments;

/* PIPEX FUNCTIONS */
void	child_process(t_arguments *arguments, int child);
void	open_files(t_arguments *arguments, char ***args);
void	close_all(t_arguments *arguments, int pid1, int pid2);
void	data_init(t_arguments **arguments, char ****args, int argc);
void	fork_function(t_arguments *arguments, char ***args, int pid1, int pid2);

/* PARSING FUNCTIONS */
int		check_args(t_arguments *arguments);
char	*get_cmds_path(char	*path, char	*cmd);
int		get_args(char ***args, t_arguments *arguments);
int		get_cmd_path(char **env, t_arguments *arguments, char ***args);
void	parse_args(char ***args, char *argv[], int *i, t_arguments *arguments);

/* FREE FUNCTIONS */
void	free_array(char **array);
void	free_args(char ***args);
void	free_arguments(t_arguments *arguments);
void	last_free(t_arguments *arguments, char ***args);
void	free_all(t_arguments *arguments, char ***args, char *error);

/* UTILS */
int		array_len(char **str_array);
#endif
