/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signal.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcarmet <tcarmet@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/05/25 15:16:49 by tcarmet           #+#    #+#             */
/*   Updated: 2015/05/25 19:46:37 by tcarmet          ###   ########.fr       */
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
	kill(all->pid_shell, SIGINT);
}

void	ft_script_signal(t_all *all)
{
	all->sig_new.sa_handler = ft_terminate_sig;
	if (sigaction(SIGINT, NULL, &(all->sig_old)) < 0)
		ft_error(SIG_FAIL);
	if (all->sig_old.sa_handler != SIG_IGN)
		sigaction(SIGINT, &(all->sig_new), NULL);
	// else if (all->sig_old.sa_handler == SIG_DFL)
	// 	return ;
	// else if (all->sig_old.sa_handler != SIG_IGN)
	// 	kill(all->pid_shell, SIGINT);
  /* SIGINT is handled in the default, fatal manner. */
	/*else if (all->sig_old.sa_handler == SIG_IGN)
		ft_putendl("OLE OLA");*/
  /* SIGINT is ignored. */
	/*else
		ft_putendl("ICI");*/
  /* A programmer-defined signal handler is in effect. */
}
