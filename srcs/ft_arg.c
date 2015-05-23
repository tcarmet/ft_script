/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arg.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/22 17:42:06 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/23 19:27:39 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_check_option(char *str, t_all *all)
{
	while (str++ && *str)
	{
		if (*str == 'a')
			APPEND = 1;
		else if (*str == 'q')
			QUIET = 1;
		else if (*str != 'a' || *str != 'q')
			ft_str_error(ARG_FAIL, &(*str));
	}
}

void	ft_check_arg(t_all *all, char **av)
{
	int i;

	i = 1;
	while (av[i])
	{
		if (av[i][0] == '-' && !FILE)
			ft_check_option(av[i], all);
		else if (av[i] && !FILE)
			FILE = i;
		else if (av[i] && !CMD)
			CMD = i;
		i++;
	}
}
