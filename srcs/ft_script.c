/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_script.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/19 17:45:45 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/19 22:12:59 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

void	ft_check_arg(char **argv, t_all *all)
{
	int i;

	
}

int		main(int argc, char **argv, char **env)
{
	t_all	all;

	all = NULL;
	if (argc >= 2)
		ft_check_arg(argv, &all);
	return (0);
	(void)env;
}
