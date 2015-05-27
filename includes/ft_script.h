/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:47:06 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/27 14:25:09 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SCRIPT_H
# define FT_SCRIPT_H
# include "libft.h"
# include <fcntl.h>
# include <time.h>
# include <signal.h>
# include <sys/select.h>
# include <sys/ioctl.h>
# include <sys/time.h>
# include <sys/wait.h>
# include <signal.h>
# define IN 1
# define OUT 0
# define QUIET all->arg[0]
# define APPEND all->arg[1]
# define FILE all->arg[2]
# define CMD all->arg[3]
# define PATH "PATH=/usr/local/bin:/usr/bin:/bin:/usr/sbin:/sbin"
# define FLAG O_RDWR | O_CREAT | (APPEND ? O_APPEND : O_TRUNC) , S_IRWXU
# define DEFAULT_FILE "typescript"

typedef enum			e_enum
{
	PIPE_FAIL = 1,
	FORK_FAIL,
	SHELL_FAIL,
	ARG_FAIL,
	OPEN_FAIL,
	BEGIN,
	END,
	PATH_FAIL,
	CMD_FAIL,
	SIG_FAIL,
	PTY_FAIL,
}						t_error;

typedef struct			s_all
{
	fd_set				set;
	struct sigaction	sig_new;
	// struct sigaction	sig_old;
	struct timeval		time;
	pid_t				pid_shell;
	int					pipe[2];
	int					fd;
	int					fd_master;
	int					fd_slave;
	int					pty;
	int					arg[4];
}						t_all;

/*
**	misc.c
*/
int						ft_error(int error);
int						ft_str_error(int error, char *str);
void					ft_aff(t_all *all, char *str, int i);
/*
**	ft_arg.c
*/
void					ft_check_option(char *str, t_all *all);
void					ft_check_arg(t_all *all, char **av);
/*
**	ft_init.c
*/
void					ft_init_all(t_all *all, char **av, char **env);
void					ft_init(t_all *all, char **env, char **av);
/*
**	ft_signal.c
*/
t_all					*ft_stock(t_all *all, int i);
void					ft_script_signal(t_all *all);
/*
**	ft_script.c
*/
void					ft_exec_arg(char **env, char **av, int i, int j);
void					ft_exec_cmd(char **env, char **av);
void					ft_read(t_all *all);
void					ft_script(t_all *all, char **av);
#endif
