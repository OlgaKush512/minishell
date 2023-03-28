/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:15:03 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/03 13:25:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_pwds(t_simple_command *c_table, char *oldpwd, char *newpwd)
{
	int	i;

	i = 0;
	while (c_table->env[i])
	{
		if (ft_strncmp("OLDPWD", c_table->env[i], ft_strlen("OLDPWD")) == 0)
		{
			free(c_table->env[i]);
			c_table->env[i] = oldpwd;
		}
		else if (ft_strncmp("PWD=", c_table->env[i], ft_strlen("PWD=")) == 0)
		{
			free(c_table->env[i]);
			c_table->env[i] = newpwd;
		}
		i++;
	}	
}

int	cd_path(t_simple_command *c_table, char **path, char *temp)
{
	int		i;
	char	*complete;

	i = 0;
	while (path[i])
	{
		complete = ft_strjoin(path[i], temp);
		c_table->last_ret = chdir(complete);
		if (c_table->last_ret == 0)
		{
			ft_bi_pwd(c_table);
			free(temp);
			free(complete);
			ft_free_3dtab(path);
			return (1);
		}
		free(complete);
		i++;
	}
	return (0);
}
