/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/08 11:38:02 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*make_pwd(char *prefix)
{
	char	wd[PATH_MAX];

	if (!getcwd(wd, PATH_MAX))
	{
		perror("minishell: cd: ");
		return (ft_strdup(prefix));
	}
	if (prefix)
		return (ft_strjoin(prefix, wd));
	else
		return (ft_strdup(wd));
}

int	ft_isbuiltin(char *str)
{
	if (ft_strcmp(str, "echo") == 0)
		return (1);
	else if (ft_strcmp(str, "cd") == 0)
		return (1);
	else if (ft_strcmp(str, "pwd") == 0)
		return (1);
	else if (ft_strcmp(str, "export") == 0)
		return (1);
	else if (ft_strcmp(str, "unset") == 0)
		return (1);
	else if (ft_strcmp(str, "env") == 0)
		return (1);
	else if (ft_strcmp(str, "exit") == 0)
		return (1);
	return (0);
}

void	start_builtin(t_simple_command **c_table)
{
	if (ft_strcmp((*c_table)->cmd, "echo") == 0)
		ft_bi_echo(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "cd") == 0)
		ft_bi_cd(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "pwd") == 0)
		ft_bi_pwd(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "export") == 0)
		ft_bi_export(c_table);
	else if (ft_strcmp((*c_table)->cmd, "unset") == 0)
		ft_bi_unset(c_table);
	else if (ft_strcmp((*c_table)->cmd, "env") == 0)
		ft_bi_env(*c_table);
	else if (ft_strcmp((*c_table)->cmd, "exit") == 0)
		ft_bi_exit(*c_table);
}

void	ft_split_builtin(t_simple_command **c_table)
{
	int	stdout;

	if (ft_strcmp((*c_table)->cmd, "exit") != 0)
	{
		stdout = dup(STDOUT_FILENO);
		if (stdout < 0)
			return (perror("minishell : dup"));
	}
	if ((*c_table)->outfile >= 0)
	{
		if (dup2((*c_table)->outfile, STDOUT_FILENO) < 0)
			return (perror("minishell: dup2"));
	}
	start_builtin(c_table);
	if (dup2(stdout, STDOUT_FILENO) < 0)
		perror("minishell: dup2");
	close (stdout);
}
