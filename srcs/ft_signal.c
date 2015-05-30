/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 15:16:49 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/30 19:45:01 by tcarmet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_script.h"

t_all	*ft_stock(t_all *all, int i)
{
	static t_all *tmp = NULL;

	if (i == 0)
		tmp = all;
	return (tmp);
}

void	ft_terminate_sig(int i)
{
	(void)i;
	kill(STOCK->pid_shell, SIGINT);
}

void	ft_script_signal(void)
{
	struct sigaction	sig_new;

	sig_new.sa_handler = ft_terminate_sig;
	sigaction(SIGINT, &sig_new, NULL);
}
