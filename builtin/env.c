/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:46 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/11/30 12:04:03 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bi_env(t_simple_command *c_table)
{
	int	i;

	i = 0;
	if (c_table->args[1] != NULL)
	{
		write(2, "minishell: env: too many arguments\n", 36);
		c_table->last_ret = 1;
		return ;
	}
	while (c_table->env[i])
	{
		write(1, c_table->env[i], ft_strlen(c_table->env[i]));
		write(1, "\n", 1);
		i++;
	}
	c_table->last_ret = 0;
}
