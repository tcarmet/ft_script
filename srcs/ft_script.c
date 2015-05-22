/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 12:20:10 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 22:18:44 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_init_all(t_all *all)
{
	ft_bzero(all->arg, 4);
}

void	ft_init(t_all *all, char **env)
{	
	char	*shell[] = {"/bin/csh", NULL};

	if (pipe(all->pipe) < 0)
		ft_error(PIPE_FAIL, ' ');
	all->pid_shell = fork();
	if (all->pid_shell < 0)
		ft_error(FORK_FAIL, ' ');
	if (all->pid_shell == 0)
	{
		dup2(all->pipe[IN], 1);
		dup2(all->pipe[IN], 2);
		dup2(all->pipe[IN], 3);
		close(all->pipe[IN]);
		execve(shell[0], shell, env);
		ft_error(SHELL_FAIL, ' ');
	}
}

void	ft_read(t_all *all)
{
	int		i;
	char	c[1025];

	ft_bzero(c, 1025);
	while ((i = read(all->pipe[OUT], c, 1024)) > 0)
	{
		write(1, c, i);
		write(all->fd, c, i);
		ft_bzero(c, 1025);
	}
}

void	ft_script(t_all *all, char **av)
{
	all->fd = 0;
	gettimeofday(&(all->time), NULL);
	if (FILE)
	{
		if ((all->fd = open(av[FILE], FLAG)) < 0)
			ft_error(OPEN_FAIL, ' ');
		ft_aff(all, av[FILE]);
	}
	if (all->fd == 0)
	{
		if ((all->fd = open("typescript", FLAG)) < 0)
			ft_error(OPEN_FAIL, ' ');
		ft_aff(all, "typescript");
	}
	ft_read(all);
}

int		main(int ac, char **av, char **env)
{
	t_all all;

	ft_init_all(&all);
	if (ac >= 2)
		ft_check_arg(&all, av);
	ft_init(&all, env);
	ft_script(&all, av);
	return (0);
}
