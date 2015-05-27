/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 17:21:18 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/27 15:49:38 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

char	*ft_getptyname(int fd_master)
{
	static char name[128];

	if (ioctl(fd_master, TIOCPTYGNAME, name) < 0)
		return (NULL);
	return (name);
}

void	ft_open_pty(t_all *all)
{
	if ((all->fd_master = open("/dev/ptmx", O_RDWR | O_NOCTTY)) < 0)
		ft_error(PTY_FAIL);
	ioctl(all->fd_master, TIOCPTYGRANT);
	ioctl(all->fd_master, TIOCPTYUNLK);
	if ((all->fd_slave = open
		(ft_getptyname(all->fd_master), O_RDWR | O_NOCTTY)) == -1)
		ft_error(PTY_FAIL);
}

void	ft_init_all(t_all *all, char **av, char **env)
{
	if (!env[0])
		env[0] = PATH;
	av[0] = DEFAULT_FILE;
	ft_open_pty(all);
	FD_ZERO(&(all->set));
	ft_bzero(all->arg, 4);
}

int			init_pty(int fd_slave)
{
	setsid();
	if (ioctl(fd_slave, TIOCSCTTY, NULL) == -1)
		return (0);
	dup2(fd_slave, 0);
	dup2(fd_slave, 1);
	dup2(fd_slave, 2);
	if (fd_slave > 2)
		close(fd_slave);
	return (1);
}


void	ft_init(t_all *all, char **env, char **av)
{
	char	*shell[2];

	shell[0] = "/bin/zsh";
	shell[1] = NULL;
	if (pipe(all->pipe) < 0)
		ft_error(PIPE_FAIL);
	all->pid_shell = fork();
	if (all->pid_shell < 0)
		ft_error(FORK_FAIL);
	if (all->pid_shell == 0)
	{
		if (!init_pty(all->fd_slave))
			ft_error(PTY_FAIL);
		if (!CMD)
			execve(shell[0], shell, env);
		else
			ft_exec_cmd(env, av + CMD);
		ft_error(SHELL_FAIL);
	}
}
