/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_handlers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:57:01 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/23 11:00:05 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	inthandler(int sig)
{
	extern int	g_signum;

	(void)sig;
	g_signum = 130;
	write(0, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	quithandler(int sig)
{
	extern int	g_signum;

	(void)sig;
	write(0, "\b\b  \b\b", 6);
}

void	inthandler2(int sig)
{
	extern int	g_signum;

	(void)sig;
	signal(SIGINT, SIG_IGN);
	g_signum = 130;
	write(0, "\n", 1);
}

void	quithandler2(int sig)
{
	extern int	g_signum;

	(void)sig;
	signal(SIGQUIT, SIG_IGN);
	g_signum = 131;
	write(2, "Quit (core dumped)\n", 19);
}

void	inthandler3(int sig)
{
	extern int	g_signum;

	(void)sig;
	g_signum = 130;
	close(STDIN_FILENO);
}
