/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 12:20:10 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 19:38:40 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_init(t_all *all, char **env)
{	
	char	*shell[] = {"/bin/zsh", NULL};

	if (pipe(all->pipe) < 0)
		ft_error(PIPE_FAIL, ' ');
	all->pid = fork();
	if (all->pid < 0)
		ft_error(FORK_FAIL, ' ');
	if (all->pid == 0)
	{
		dup2(all->pipe[IN], 1);
		dup2(all->pipe[IN], 2);
		dup2(all->pipe[IN], 3);
		close(all->pipe[IN]);
		execve(shell[0], shell, env);
		ft_error(SHELL_FAIL, ' ');
	}
}

void	ft_script(t_all *all, char **av)
{
	char	c[1025];
	int		i;

	all->fd = -1;
	gettimeofday(&(all->time), NULL);
	if (all->file)
	{
		all->fd = open(av[all->file], O_TRUNC | O_RDWR | O_CREAT);
		ft_aff(all, av[all->file]);
	}
	if (all->fd == -1)
	{
		all->fd = open("typescript", O_TRUNC | O_RDWR | O_CREAT);
		ft_aff(all, "typescript");
	}
	ft_bzero(c, ft_strlen(c));
	while ((i = read(all->pipe[OUT], c, 1024)) > 0)
	{
		if (c)
		{
			write(1, c, i);
			write(all->fd, c, i);
			ft_bzero(c, ft_strlen(c));
		}
	}
}

int		main(int ac, char **av, char **env)
{
	t_all all;

	all.file = 0;
	all.cmd = 0;
	if (ac >= 2)
		ft_check_arg(&all, av);
	ft_init(&all, env);
	ft_script(&all, av);
	return (0);
}
