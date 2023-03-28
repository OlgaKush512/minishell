/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:29 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/07 15:00:11 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_bi_pwd(t_simple_command *c_table)
{
	char	wd[PATH_MAX];

	if (!getcwd(wd, PATH_MAX))
	{
		perror("minishell: error");
		c_table->last_ret = 1;
	}
	else
	{
		write(1, wd, ft_strlen(wd));
		write(1, "\n", 2);
		c_table->last_ret = 0;
	}
}
