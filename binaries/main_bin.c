/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bin.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/16 10:32:57 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	stat_management(char *bin, int mode)
{
	if (mode / 1000 == 16 && ft_strncmp(bin, "./", 2) == 0)
		return (cant_exec(bin, ": Is a directory\n", 126));
	if (ft_strncmp(bin, "./", 2) == 0 && mode != 0 && mode % 33000 / 200 != 1)
		return (cant_exec(bin, ": Permission denied\n", 126));
	if (mode == 0 && (ft_strncmp(bin, "./", 2) == 0 || bin[0] == '/'))
		return (cant_exec(bin, ": No such file or directory\n", 127));
	if (((mode % 33000) / 200) == 0 || mode / 1000 == 16)
		return (cant_exec(bin, ": command not found\n", 127));
	return (0);
}

int	get_stat(char *str)
{
	struct stat	*buf;
	int			ret;

	buf = malloc(sizeof(struct stat));
	if (buf == NULL)
		return (-1);
	buf->st_mode = 0;
	if (buf == NULL)
		return (0);
	stat(str, buf);
	ret = buf->st_mode;
	free(buf);
	return (ret);
}

void	execution(t_simple_command *c_ta, char **env)
{
	int	mode;

	mode = get_stat(c_ta->args[0]);
	if (check_exec(mode, c_ta))
	{
		if (c_ta->outfile >= 0)
		{
			if (dup2(c_ta->outfile, STDOUT_FILENO) < 0)
				perror("minishell :error");
		}
		if (c_ta->infile >= 0)
		{
			if (dup2(c_ta->infile, STDIN_FILENO) < 0)
				perror("minishell :error");
		}
		c_ta->last_ret = stat_management(c_ta->args[0], mode);
		if (c_ta->last_ret == 0)
		{
			execve(c_ta->args[0], c_ta->args, env);
			perror("minishell : execve");
			c_ta->last_ret = 126;
		}
	}
	else
		c_ta->last_ret = cant_exec(c_ta->cmd, " : command not found\n", 127);
}

void	ft_bin_nofork(t_simple_command *c_table, char **env)
{
	char	**path;

	path = ft_get_paths(env);
	if (path == NULL && c_table->cmd[0] != '/')
		cant_exec(c_table->cmd, ": No such file or directory\n", 127);
	ft_add_path(c_table, path);
	execution(c_table, env);
}

void	ft_exec_bin(t_simple_command *c_table, char **env)
{
	char	**path;
	pid_t	child;

	path = ft_get_paths(env);
	if (path == NULL && c_table->cmd[0] != '/')
		return (no_path(c_table, 127));
	ft_add_path(c_table, path);
	if (c_table->args_num != 0)
	{
		child = fork();
		if (child < 0)
			return (perror("minishell: fork : "));
		if (child == 0)
		{
			execution(c_table, env);
			exit(free_one_memb(c_table, NULL, NULL, c_table->last_ret));
		}
		else if (child > 0)
			set_signals2();
		waitpid(child, &c_table->last_ret, 0);
		c_table->last_ret = WEXITSTATUS(c_table->last_ret);
	}
	else
		c_table->last_ret = 0;
}
