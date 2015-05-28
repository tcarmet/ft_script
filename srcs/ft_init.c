/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 17:21:18 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/28 19:47:48 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_term(int status)
{
	struct termios term;

	ioctl(0, TIOCGETA, &term);
	if (status == RESTORE)
		term.c_lflag |= (ICANON | ECHO);
	else
		term.c_lflag &= ~(ECHO | ICANON);
	ioctl(0, TIOCSETA, &term);
}

void	ft_open_pty(t_all *all)
{
	static char name[256];

	if ((all->fd_master = open("/dev/ptmx", O_RDWR | O_NOCTTY)) < 0)
		ft_error(PTY_FAIL);
	if ((ioctl(all->fd_master, TIOCPTYGRANT)) < 0)
		ft_error(PTY_FAIL);
	if ((ioctl(all->fd_master, TIOCPTYUNLK)) < 0)
		ft_error(PTY_FAIL);
	if (ioctl(all->fd_master, TIOCPTYGNAME, name) < 0)
		ft_error(PTY_FAIL);
	if ((all->fd_slave = open(name, O_RDWR | O_NOCTTY)) == -1)
		ft_error(PTY_FAIL);
}

void	ft_init_all(t_all *all, char **av, char **env)
{

	if (!env[0])
		env[0] = PATH;
	av[0] = DEFAULT_FILE;
	ft_term(INIT);
	ft_open_pty(all);
	ft_bzero(all->arg, 4);
}

int			init_pty(t_all *all)
{
	setsid();
	if (ioctl(all->fd_slave, TIOCSCTTY, NULL) == -1)
		return (FALSE);
	close(all->fd_master);
	dup2(all->fd_slave, 0);
	dup2(all->fd_slave, 1);
	dup2(all->fd_slave, 2);
	if (all->fd_slave > 2)
		close(all->fd_slave);
	return (TRUE);
}


void	ft_init(t_all *all, char **env, char **av)
{
	char	*shell[2];

	shell[0] = "/bin/zsh";
	shell[1] = NULL;
	all->pid_shell = fork();
	if (all->pid_shell < 0)
		ft_error(FORK_FAIL);
	if (all->pid_shell == 0)
	{
		if (!init_pty(all))
			ft_error(PTY_FAIL);
		if (!CMD)
			execve(shell[0], shell, env);
		else
			ft_exec_cmd(env, av + CMD);
		ft_error(SHELL_FAIL);
	}
}
