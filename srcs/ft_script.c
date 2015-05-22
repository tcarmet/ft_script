/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 12:20:10 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 23:32:59 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_init_all(t_all *all)
{
	ft_bzero(all->arg, 4);
}

// void	ft_exec_cmd(t_all *all, char **env, char **av)
// {
// 	int i;

// 	i = 0;
// 	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
// 		i++;

// }

void	ft_init(t_all *all, char **env/*, char **av*/)
{	
	char	*shell[2];

	shell[0] = "/bin/csh";
	shell[1] = NULL;
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
		if (!CMD)
			execve(shell[0], shell, env);
		// else
		// 	ft_exec_cmd(all, env, av);
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
	if ((all->fd = open(av[FILE], FLAG)) < 0)
		ft_error(OPEN_FAIL, ' ');
	ft_aff(all, av[FILE], BEGIN);
	all->pid_read = fork();
	if (all->pid_read < 0)
		ft_error(FORK_FAIL, ' ');
	if (all->pid_read == 0)
		ft_read(all);
	waitpid(all->pid_shell, NULL, WUNTRACED);
	kill(all->pid_read, 9);
	ft_aff(all, av[FILE], END);
}

int		main(int ac, char **av, char **env)
{
	t_all all;

	ft_init_all(&all);
	av[0] = "typescript";
	if (ac >= 2)
		ft_check_arg(&all, av);
	ft_init(&all, env/*, av*/);
	ft_script(&all, av);
	return (0);
}
