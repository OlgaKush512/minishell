/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_var_existe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 11:55:46 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/20 10:49:41 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	skip_redir(t_token *temp, int len, int y)
{
	while (y < len && temp[y].type >= RED_OUT && temp[y].type <= RED_HERE_DOC)
		y += 2;
	return (y);
}

int	check_var_env(char **env, t_token *temp, int y)
{
	char	*str;
	int		i;

	i = 0;
	while (env[i])
	{
		str = ft_var_only(env[i]);
		if ((ft_strcmp(temp[y].value, "$?") == 0) || (temp[y].type == DOLLAR
				&& ft_strcmp(str, temp[y].value + 1) == 0)
			|| ((temp[y].value != NULL) && (*(temp[y].value) == '$')
				&& !*(temp[y].value + 1)))
		{
			temp[y].subst = 1;
			free(str);
			return (1);
		}
		else if (temp[y].type == ARG)
		{
			free(str);
			return (1);
		}
		free(str);
		i++;
	}
	return (0);
}

int	do_var_existe(t_token **arr_tok, int len, char **env, int index)
{
	int		y;
	int		count;
	t_token	*temp;

	count = 0;
	y = index;
	temp = *arr_tok;
	while (y < len)
	{
		y = skip_redir(temp, len, y);
		if (y == len || temp[y].type == PIPE)
			return (count);
		temp[y].subst = 0;
		count += check_var_env(env, temp, y);
		if (temp[y].type == DOLLAR && temp[y].subst == 0)
		{
			free(temp[y].value);
			temp[y].value = NULL;
		}
		y++;
	}
	return (count);
}
