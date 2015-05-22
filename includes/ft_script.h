/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:47:06 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 17:56:52 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H
# include "libft.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <signal.h>
# define IN 1
# define OUT 0
# define QUIET 0
# define APPEND 1

typedef enum	e_enum
{
	PIPE_FAIL = 1,
	FORK_FAIL,
	SHELL_FAIL,
	ARG_FAIL,
}				t_error;

typedef struct	s_all
{
	pid_t	pid;
	int		pipe[2];
	int		fd;
	int		arg[2];
	int		file;
	int		cmd; 
}				t_all;

/*
**	misc.c
*/
int		ft_error(int error, char c);
/*
**	ft_arg.c
*/
void	ft_check_option(char *str, t_all *all);
void	ft_check_arg(t_all *all, char **av);

#endif

