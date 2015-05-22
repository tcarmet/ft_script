/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:47:06 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 21:52:23 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H
# include "libft.h"
# include <fcntl.h>
# include <time.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# define IN 1
# define OUT 0
# define QUIET all->arg[0]
# define APPEND all->arg[1]
# define FILE all->arg[2]
# define CMD all->arg[3]
# define FLAG O_RDWR | O_CREAT | (APPEND ? O_APPEND : O_TRUNC), S_IRWXU

typedef enum	e_enum
{
	PIPE_FAIL = 1,
	FORK_FAIL,
	SHELL_FAIL,
	ARG_FAIL,
	OPEN_FAIL,
}				t_error;

typedef struct	s_all
{
	struct	timeval time;
	pid_t	pid_shell;
	pid_t	pid_read;
	int		pipe[2];
	int		fd;
	int		arg[4];
}				t_all;

/*
**	misc.c
*/
int		ft_error(int error, char c);
void	ft_aff(t_all *all, char *str);
/*
**	ft_arg.c
*/
void	ft_check_option(char *str, t_all *all);
void	ft_check_arg(t_all *all, char **av);

#endif

