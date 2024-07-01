/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:27:02 by daduarte          #+#    #+#             */
/*   Updated: 2024/07/01 16:35:29 by daduarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
# include "../ft_printf/includes/ft_printf.h"
# include "../ft_printf/includes/libft.h"

extern	char	**environ;

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

/* PARSING FUNCTIONS */
char	*get_path(char **env);
int		*check_args(t_arguments *arguments);
char	*get_cmd_path(char	*path, char	*cmd);
int		get_args(char ***args, t_arguments *arguments);

/* FREE FUNCTIONS */
void	free_array(char **array);
void	free_args(char ***args, int	len);
void	free_arguments(t_arguments *arguments);
void	free_all(t_arguments *arguments, char **args, int len, char *error);

/* UTILS */
int		array_len(char **str_array);
#endif

