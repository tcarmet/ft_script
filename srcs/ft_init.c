/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_init.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/23 17:21:18 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/23 19:27:36 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_init_all(t_all *all, char **av, char **env)
{
	if (!env[0])
		env[0] = PATH;
	av[0] = "typescript";
	ft_bzero(all->arg, 4);
}

void	ft_init(t_all *all, char **env, char **av)
{
	char	*shell[2];

	shell[0] = "/bin/csh";
	shell[1] = NULL;
	if (pipe(all->pipe) < 0)
		ft_error(PIPE_FAIL);
	all->pid_shell = fork();
	if (all->pid_shell < 0)
		ft_error(FORK_FAIL);
	if (all->pid_shell == 0)
	{
		dup2(all->pipe[IN], 1);
		dup2(all->pipe[IN], 2);
		dup2(all->pipe[IN], 3);
		close(all->pipe[OUT]);
		if (!CMD)
			execve(shell[0], shell, env);
		else
			ft_exec_cmd(env, av + CMD);
		ft_error(SHELL_FAIL);
	}
}
