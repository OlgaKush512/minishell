/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:57:47 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/16 10:39:52 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_strccmp(char *s1, char *s2, char c)
{
	int	i;

	i = 0;
	while (s1[i] && s1[i] != c && s2[i] && s2[i] != c && s1[i] == s2[i])
		i++;
	if (s1[i] == s2[i] || (s2[i] == 0 && s1[i] == c)
		|| (s1[i] == 0 && s2[i] == c))
		return (0);
	return (1);
}

int	is_in_env(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strccmp(str, env[i], '=') == 0)
			return (1);
		else
			i++;
	}
	return (0);
}

void	ft_remove_from_env(char *str, char ***env)
{
	int		i;
	char	**res;
	int		j;

	i = 0;
	j = 0;
	while ((*env)[i])
		i++;
	res = malloc(sizeof(char *) * i);
	if (res == NULL)
		return ;
	i = 0;
	while ((*env)[j])
	{
		if (ft_strccmp(str, (*env)[j], '=') != 0)
			res[i++] = (*env)[j++];
		else
			free((*env)[j++]);
	}
	res[i] = NULL;
	free(*env);
	(*env) = res;
}

void	ft_bi_unset(t_simple_command **c_table)
{
	int	i;

	i = 1;
	(*c_table)->last_ret = 0;
	while ((*c_table)->args[i])
	{
		if (is_in_env((*c_table)->args[i], (*c_table)->env)
			&& is_valid_export((*c_table)->args[i]) == 0)
			ft_remove_from_env((*c_table)->args[i], &(*c_table)->env);
		else
		{
			if (is_valid_export((*c_table)->args[i]))
			{
				write(2, "minishell: unset : `", 21);
				write(2, (*c_table)->args[i], ft_strlen((*c_table)->args[i]));
				write(2, "': not a valid identifier", 26);
				write(2, "\n", 1);
				(*c_table)->last_ret = 1;
			}
		}
		i++;
	}
}
