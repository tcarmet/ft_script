/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 12:20:10 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/25 11:47:10 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_exec_arg(char **env, char **av, int i, int j)
{
	char	path[1024];
	int		k;
	int		l;

	l = 0;
	while (env[i][j] && env[i][j] != ':' && env[i][j] != '=')
		path[l++] = env[i][j++];
	path[l++] = '/';
	k = 0;
	while (av[0][k] && av[0][k] != '/')
		path[l++] = av[0][k++];
	path[l] = 0;
	if (av[0][k] == '/' && !access(path, X_OK))
		execve(av[0], av, env);
	if (!access(path, X_OK))
		execve(path, av, env);
}

void	ft_exec_cmd(char **env, char **av)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (env[i] && ft_strncmp(env[i], "PATH=", 5))
		i++;
	while (env[i][j])
	{
		ft_exec_arg(env, av, i, j);
		j++;
	}
	ft_str_error(CMD_FAIL, av[0]);
}

void	ft_read(t_all *all)
{
	int		i;
	char	c[1025];

	ft_bzero(c, 1025);
	close(all->pipe[IN]);
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
		ft_str_error(OPEN_FAIL, av[FILE]);
	ft_aff(all, av[FILE], BEGIN);
	ft_read(all);
	ft_aff(all, av[FILE], END);
}

int		main(int ac, char **av, char **env)
{
	t_all all;

	ft_init_all(&all, av, env);
	if (ac >= 2)
		ft_check_arg(&all, av);
	ft_init(&all, env, av);
	ft_script(&all, av);
	return (0);
}
