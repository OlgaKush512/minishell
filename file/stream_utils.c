/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stream_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/23 10:54:44 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/23 10:58:54 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	save_stdin(void)
{
	int	res;

	res = dup(STDIN_FILENO);
	if (res < 0)
		perror("dup");
	return (res);
}

void	stdin_getback(int saved)
{
	extern int	g_signum;
	int			ret;

	if (g_signum == 130)
	{
		ret = dup2(saved, STDIN_FILENO);
		if (ret < 0)
			perror("dup2");
		write(0, "\n", 1);
	}
	close(saved);
}

void	ft_close_prev(t_simple_command *c_table)
{
	if (c_table->outfile >= 0)
		close(c_table->outfile);
	if (c_table->infile >= 0)
		close(c_table->infile);
	c_table->outfile = -42000;
	c_table->infile = -42000;
}
