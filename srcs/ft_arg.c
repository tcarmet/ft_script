/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 17:42:06 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 18:07:36 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_check_option(char *str, t_all *all)
{
	int i;

	i = 1;
	while (str[i])
	{
		if (str[i] == 'a')
			all->arg[APPEND] = 1;
		else if (str[i] == 'q')
			all->arg[QUIET] = 1;
		else if (str[i] != 'a' || str[i] != 'q')
			ft_error(ARG_FAIL, str[i]);
		i++;
	}
}

void	ft_check_arg(t_all *all, char **av)
{
	int i;
	int count;

	i = 1;
	count = 0;
	while (av[i])
	{
		if (av[i][0] == '-')
			ft_check_option(av[i], all);
		else if (av[i] && count == 0)
		{
			all->file = i;
			count++;
		}
		else if (av[i] && count == 1)
			all->cmd = i;
		i++;
	}
}