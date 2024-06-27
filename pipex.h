/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: daduarte <daduarte@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/27 14:27:02 by daduarte          #+#    #+#             */
/*   Updated: 2024/06/27 15:40:11 by daduarte         ###   ########.fr       */
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

typedef struct s_arguments
{
	char	**env_cmds;
	char	**cmd1;
	char	**cmd2;
	char	*infile;
	char	*outfile;
}	t_arguments;

#endif

