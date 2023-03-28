/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools_parser.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 12:15:31 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/16 11:03:06 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*ft_var_only(char *str)
{
	int		i;
	int		end;
	char	*res;

	i = 0;
	end = 0;
	while (str[end + 1] != '=' && str[end + 1])
		end++;
	if (str[end + 1] == 0)
		return (NULL);
	res = malloc(sizeof(char) * end + 2);
	if (res == NULL)
		return (NULL);
	while (i <= end)
	{
		res[i] = str[i];
		i++;
	}
	res[i] = 0;
	return (res);
}

char	*ft_add_var(char *str)
{
	int		i;
	char	*res;
	int		j;

	i = 0;
	while ((ft_strncmp(str + i, "=", 1) != 0) && str[i])
		i++;
	i += 1;
	res = malloc(sizeof(char) * ft_strlen(str + i) + 1);
	j = 0;
	while (str[i])
		res[j++] = str[i++];
	res[j] = 0;
	return (res);
}

char	*new_var(char *temp, char *str, char *new)
{
	free(temp);
	free(str);
	return (ft_add_var(new));
}

char	*ft_exp_dol(char *str, int mode, char **env, int ret)
{
	int		i;
	char	*temp;

	i = 0;
	if (!str)
		return (NULL);
	if ((str[0] != '$' || mode == 8 || mode == 1)
		|| (str[0] == '$' && !str[1]))
		return (str);
	if (ft_strcmp("$?", str) == 0)
	{
		free(str);
		return (ft_itoa(ret));
	}
	while (env[i])
	{
		temp = ft_var_only(env[i]);
		if (ft_strcmp(temp, str + 1) == 0)
			return (new_var(temp, str, env[i]));
		free(temp);
		i++;
	}
	free(str);
	return (NULL);
}

void	ft_free_redir(t_redir **list)
{
	t_redir	*temp;

	if (*list == NULL)
		return ;
	while (*list)
	{
		temp = *list;
		*list = (*list)->next;
		free(temp->file);
		free(temp);
	}
	*list = NULL;
}
