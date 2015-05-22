/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:45:45 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 12:19:16 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>

#define BUFF 1024
#define TERN O_RDWR | O_CREAT | (ft_aff(NULL, 3) ? O_APPEND : O_TRUNC), S_IRWXU
#define PA (env[i[0]][0] != 'P' || env[i[0]][1] != 'A'
#define TH env[i[0]][2] != 'T' || env[i[0]][3] != 'H' || env[i[0]][4] != '=')
#define EQ  env[i[0]][i[2]] != ':' && env[i[0]][i[2]] != '='
#define W write(i[0], "Script started\n", 15), write(1, "Script started\n", 15)


int		ft_aff(char *s, int fd)
{
	int				i;
	static int		a = 0;
	static int		q = 0;

	if (fd == 'a')
		return (a = 1);
	if (fd == 'q')
		return (q = 1);
	if (fd == 3)
		return (a);
	if (fd == 4)
		return (q);
	i = 0;
	while (s[i])
		i++;
	return (write(fd, s, i));
}

int		charzero(void *av, int fc)
{
	int	i;

	i = 0;
	if (fc == 0)
		while (i <= BUFF)
			((char *)av)[i++] = 0;
	else if (fc == 1 && ++(*(char ***)av))
		while (*(*(char ***)av) && (*(*(char ***)av))[0] == '-')
		{
			while ((*(*(char ***)av))[0])
			{
				if ((*(*(char ***)av))[0] == 'a')
					ft_aff(NULL, 'a');
				else if ((*(*(char ***)av))[0] == 'q')
					ft_aff(NULL, 'q');
				else if ((*(*(char ***)av))[0] != '-')
					_exit(ft_aff("Error : illegal options\n\
usage: ./ft_script [-aq] [file [command ...]]\n", 2));
				(*(*(char ***)av))++;
			}
			(*(char ***)av)++;
		}
	return (1);
}

void	norme(int *f, int *p, char **av)
{
	char		c[BUFF + 1];
	int			i[2];

	if ((i[0] = -1) && av[0])
		i[0] = open(av[0], TERN);
	if (i[0] == -1)
		i[0] = open("typescript", TERN);
	if ((f[1] = fork()) && f[1] < 0)
		_exit(ft_aff("Error: fork failed\n", 2));
	if (f[1] == 0)
	{
		if (!ft_aff(NULL, 4))
			W;
		while (charzero(c, 0) && (i[1] = read(p[0], c, BUFF)) > 0)
			write(1, c, i[1]), write(i[0], c, i[1]);
		_exit(0);
	}
	else
	{
		waitpid(f[0], NULL, WUNTRACED), kill(f[1], 9);
		if (!ft_aff(NULL, 4))
			write(i[0], "Script done\n", 12), write(1, "Script done\n", 12);
		close(i[0]);
	}
}

void	exc_cmd(char **av, char **env)
{
	char	path[BUFF + 1];
	int		i[4];

	i[0] = 0;
	while (env && env[i[0]] && PA || TH)
		i[0]++;
	if (!env || (env && !env[i[0]]))
		_exit(ft_aff("Error No Paths\n", 2));
	i[2] = 0;
	while (env[i[0]][i[2]])
	{
		i[1] = 0;
		while (env[i[0]][i[2]] && EQ)
			path[i[1]++] = env[i[0]][i[2]++];
		path[i[1]++] = '/';
		i[3] = 0;
		while (av[0][i[3]] && av[0][i[3]] != '/')
			path[i[1]++] = av[0][i[3]++];
		path[i[1]] = 0;
		if (av[0][i[3]] == '/' && access(path, X_OK) == 0)
			execve(av[0], av, env);
		((access(path, X_OK) == 0) ? execve(path, av, env) : i[2]++);
	}
	_exit(ft_aff("Error : command not found\n", 2));
}

int		main(int ac, char **av, char **env)
{
	static char	*argv[] = {"/bin/csh", NULL};
	pid_t		f[2];
	int			p[2];

	charzero(&av, 1);
	if (pipe(p) < 0)
		_exit(ft_aff("Error: could not pipe\n", 2));
	f[0] = fork();
	if (f[0] < 0)
		_exit(ft_aff("Error: fork failed\n", 2));
	if (f[0] == 0)
	{
		dup2(p[1], 1);
		dup2(p[1], 2);
		dup2(p[1], 3);
		if (av[0] && ++av && av[0])
			exc_cmd(av, env);
		execve(argv[0], argv, env);
		_exit(ft_aff("Error Exiting/Executing shell\n", 2));
	}
	else
		norme(f, p, av);
	return ((ac = 0));
}
