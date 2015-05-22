/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 17:42:06 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/22 20:34:35 by tcarmet          ###   ########.fr       */
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
			APPEND = 1;
		else if (str[i] == 'q')
			QUIET = 1;
		else if (str[i] != 'a' || str[i] != 'q')
			ft_error(ARG_FAIL, str[i]);
		i++;
	}
}

void	ft_check_arg(t_all *all, char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-')
			ft_check_option(av[i], all);
		else if (av[i] && !FILE)
			FILE = i;
		else if (av[i] && !CMD)
			CMD = i;
		i++;
	}
}