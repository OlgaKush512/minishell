/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:25 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/08 11:37:47 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cd_noarg(t_simple_command *c_table)
{
	int	i;

	i = 0;
	while (c_table->env[i])
	{
		if (ft_strncmp("HOME=", c_table->env[i], 5) == 0)
		{
			if (chdir(&c_table->env[i][5]) < 0)
			{
				c_table->last_ret = 1;
				write(2, "minishell: cd: ", 16);
				write(2, &c_table->env[i][5], ft_strlen(&c_table->env[i][5]));
				perror(" ");
			}
			else
				c_table->last_ret = 0;
			return ;
		}
		i++;
	}
	write(2, "minishell: cd: HOME not set\n", 29);
	c_table->last_ret = 1;
}

int	cd_get_dash(t_simple_command *c_table)
{
	int	i;

	i = 0;
	if (ft_strncmp(c_table->args[1], "-", 1) != 0)
		return (0);
	while (c_table->env[i] && ft_strncmp("OLDPWD=", c_table->env[i], 7))
		i++;
	if (c_table->env[i] == NULL)
	{
		free(c_table->args[1]);
		c_table->args[1] = NULL;
		return (-1);
	}
	free(c_table->args[1]);
	c_table->args[1] = ft_strdup(&c_table->env[i][7]);
	return (1);
}

void	cd_curpath(t_simple_command *c_table)
{
	int		temp;
	char	*display;

	c_table->last_ret = 1;
	temp = cd_get_dash(c_table);
	if (c_table->args[1] == NULL)
	{
		write(2, "minishell: cd: OLDPWD not set\n", 31);
		return ;
	}
	if (chdir(c_table->args[1]) == -1)
	{
		write(2, "minishell: cd: ", 16);
		write(2, c_table->args[1], ft_strlen(c_table->args[1]));
		perror(" ");
	}
	else
		c_table->last_ret = 0;
	if (temp == 1 && c_table->last_ret == 0)
	{
		display = make_pwd(NULL);
		write(1, display, ft_strlen(display));
		write(1, "\n", 1);
		free(display);
	}
}

void	cd_classic(t_simple_command *c_table)
{
	char	*temp;
	int		i;
	char	**path;

	i = 0;
	if (c_table->args[1][0] == 0)
		return ;
	while (c_table->env[i] && ft_strncmp(c_table->env[i],
			"CDPATH=", ft_strlen("CDPATH=")))
		i++;
	if (c_table->env[i] == NULL)
	{
		cd_curpath(c_table);
		return ;
	}
	temp = ft_strjoin("/", c_table->args[1]);
	path = ft_split(&c_table->env[i][7], ':');
	i = 0;
	if (cd_path(c_table, path, temp) == 0)
		cd_curpath(c_table);
}

void	ft_bi_cd(t_simple_command *c_table)
{
	char	*oldpwd;
	char	*newpwd;

	oldpwd = make_pwd("OLDPWD=");
	if (c_table->args_num > 2)
	{
		write(2, "minishell: cd: trop d'arguments\n", 33);
		c_table->last_ret = 1;
	}
	else if (c_table->args_num <= 1)
		cd_noarg(c_table);
	else if (c_table->args[1][0] == '/' || c_table->args[1][0] == '.'
		|| ft_strcmp("-", c_table->args[1]) == 0)
		cd_curpath(c_table);
	else
		cd_classic(c_table);
	if (c_table->last_ret != 0)
	{
		free(oldpwd);
		return ;
	}
	newpwd = make_pwd("PWD=");
	add_pwds(c_table, oldpwd, newpwd);
}
