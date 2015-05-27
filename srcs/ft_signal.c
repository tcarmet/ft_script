/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 15:16:49 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/27 15:47:13 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "ft_script.h"

t_all	*ft_stock(t_all *all, int i)
{
	static t_all *tmp = NULL;

	if (i == 0)
		tmp = all;
	return (tmp);
}

void	ft_terminate_sig(int i)
{
	t_all *all;

	all = NULL;
	all = ft_stock(all, 1);
	(void)i;
	killpg(all->pid_shell, SIGINT);
}

void	ft_script_signal(t_all *all)
{
	all->sig_new.sa_handler = ft_terminate_sig;
	sigaction(SIGINT, &all->sig_new, NULL);
}
