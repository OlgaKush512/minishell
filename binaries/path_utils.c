/* ************************************************************************** */
/*	  		                                                                  */
/*                                                        :::      ::::::::   */
/*   path_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/10/27 10:59:38 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	cant_exec(char *file, char *message, int vexit)
{
	write(2, "minishell: ", 12);
	write(2, file, ft_strlen(file));
	write(2, message, ft_strlen(message));
	return (vexit);
}

void	ft_add_path(t_simple_command *c_table, char **path)
{
	int		i;
	char	*temp;

	i = 0;
	if (!path)
		return ;
	if (c_table->args[0][0] == 0)
		return (ft_free_3dtab(path));
	if (ft_strcmp(c_table->cmd, "..") == 0 || c_table->cmd[0] == '.')
		return (ft_free_3dtab(path));
	while (path[i])
	{
		temp = ft_strjoin(path[i], c_table->args[0]);
		if (access(temp, X_OK) == 0)
		{
			free(c_table->args[0]);
			c_table->args[0] = temp;
			ft_free_3dtab(path);
			return ;
		}
		else
			free(temp);
		i++;
	}
	ft_free_3dtab(path);
}

char	**ft_get_paths(char **envp)
{
	int		i;
	char	**res;
	char	*str;
	char	*temp;

	i = -1;
	while (envp[++i])
		if (ft_strncmp(envp[i], "PATH", 4) == 0)
			break ;
	if (envp[i] == NULL)
		return (NULL);
	temp = ft_rm_path(envp[i]);
	if (temp == NULL)
		return (NULL);
	str = ft_add_slash(temp);
	res = ft_split(str, ':');
	free(str);
	free(temp);
	return (res);
}

char	*ft_add_slash(char *res)
{
	int		i;
	int		count;
	char	*str;

	i = 0;
	count = 0;
	while (res[i])
		if (res[i++] == ':')
			count++;
	str = malloc(sizeof(char) * ft_strlen(res) + count + 1);
	if (str == NULL)
		ft_wrong_malloc();
	i = 0;
	count = 0;
	while (res[i])
	{
		if (res[i] == ':')
			str[i + count++] = '/';
		str[i + count] = res[i];
		i++;
	}
	str[i + count] = '\0';
	return (str);
}

char	*ft_rm_path(char *str)
{
	char	*res;
	int		i;

	i = 0;
	res = malloc(sizeof(char) * ft_strlen(str) - 3);
	if (res == NULL)
		return (NULL);
	while (str[i + 5])
	{
		res[i] = str[i + 5];
		i++;
	}
	res[i] = '/';
	res[i + 1] = '\0';
	return (res);
}
