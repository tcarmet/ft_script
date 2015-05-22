/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 12:27:44 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 21:39:40 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

int		ft_error(int error, char c)
{
	if (error == PIPE_FAIL)
		ft_putendl_fd("Error: could not pipe", 2);
	else if (error == FORK_FAIL)
		ft_putendl_fd("Error: could not fork", 2);
	else if (error == SHELL_FAIL)
		ft_putendl_fd("Error Exiting/Executing shell", 2);
	else if (error == ARG_FAIL)
	{
		ft_putstr_fd("script: illegal option -- ", 2);
		ft_putchar_fd(c, 2);
		ft_putendl_fd("\nusage: script [-aq] [file [command ...]]", 2);
	}
	else if (error == OPEN_FAIL)
		ft_putendl_fd("ft_script: Permission denied.", 2);
	_exit(error);
}

void	ft_aff(t_all *all, char *str)
{
	if (!QUIET)
	{
		ft_putstr("Script started, output file is ");
		ft_putendl(str);
		ft_putstr_fd("Script started on ", all->fd);
		ft_putstr_fd(ctime(&(all->time.tv_sec)), all->fd);
	}
}