/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_signals.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:56:48 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/23 11:00:10 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sig_val(int ret)
{
	extern int	g_signum;

	if (g_signum != -1)
	{
		ret = g_signum;
		g_signum = -1;
	}
	return (ret);
}

void	set_signals(void)
{
	signal(SIGINT, inthandler);
	signal(SIGQUIT, quithandler);
}

void	set_signals2(void)
{
	signal(SIGINT, inthandler2);
	signal(SIGQUIT, quithandler2);
	signal(SIGSEGV, segvhandler2);
}

void	set_signals3(void)
{
	signal(SIGINT, inthandler3);
}

void	segvhandler2(int sig)
{
	extern int	g_signum;

	(void)sig;
	signal(SIGSEGV, SIG_IGN);
	g_signum = 139;
	write(2, "Segmentation fault (core dumped)\n", 34);
}
