/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:20 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/09 16:54:25 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_nonewl(char *str, char c)
{
	int	i;

	i = 1;
	if (str == NULL || str[0] != '-')
		return (0);
	while (str[i])
	{
		if (str[i] != c)
			return (0);
		i++;
	}
	return (1);
}

void	ft_bi_echo(t_simple_command *c_table)
{
	int	i;

	i = 1;
	while (is_nonewl(c_table->args[i], 'n'))
		i++;
	while (c_table->args[i])
	{
		write(1, c_table->args[i], ft_strlen(c_table->args[i]));
		if (c_table->args[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (is_nonewl(c_table->args[1], 'n') == 0)
		write(1, "\n", 1);
	c_table->last_ret = 0;
}
