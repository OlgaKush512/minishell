/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/16 11:51:24 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

void	free_tab_pipes(pid_t *tab, int *pipes)
{
	if (tab)
		free(tab);
	if (pipes)
		free(pipes);
}

void	no_path(t_simple_command *c_table, int ret)
{
	c_table->last_ret = ret;
	cant_exec(c_table->cmd, ": No such file or directory\n", -1);
}

char	*ft_add_shlvl(char *env)
{
	int		i;
	int		lvl;
	char	*res;
	char	*temp;

	i = 6;
	lvl = ft_atoi(&env[i]);
	lvl++;
	temp = ft_itoa(lvl);
	res = ft_strjoin("SHLVL=", temp);
	free(temp);
	return (res);
}

char	**ft_empty_env(void)
{
	char	**res;

	res = malloc(sizeof(char *) * 4);
	if (res == NULL)
	{
		write(2, "env error with malloc, exiting minishell..\n", 44);
		exit(1);
	}
	res[0] = ft_strdup("OLDPWD");
	res[1] = make_pwd("PWD=");
	res[2] = ft_strdup("SHLVL=1");
	res[3] = NULL;
	return (res);
}

char	**ft_copy_env(char **env)
{
	int		i;
	int		j;
	char	**res;

	i = 0;
	j = 0;
	if (env[0] == NULL)
		return (ft_empty_env());
	while (env[i])
		i++;
	res = malloc(sizeof(char *) * (i + 1));
	if (res == NULL)
		exit(write(2, "env error with malloc, exiting minishell..\n", 44));
	while (j < i)
	{
		if (ft_strncmp("SHLVL=", env[j], ft_strlen("SHLVL=")) == 0)
			res[j] = ft_add_shlvl(env[j]);
		else
			res[j] = ft_strdup(env[j]);
		j++;
	}
	res[j] = NULL;
	return (res);
}
