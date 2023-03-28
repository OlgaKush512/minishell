/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args_parser.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 17:50:49 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/21 13:12:41 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_count_args(t_token *arr_tok, int index, int len)
{
	int	count;

	count = 0;
	while (index < len && arr_tok[index].type != PIPE)
	{
		if (arr_tok[index].type >= RED_OUT
			&& arr_tok[index].type <= RED_HERE_DOC)
			index++;
		else if (arr_tok[index].type == DOLLAR || arr_tok[index].type == ARG)
			count++;
		index++;
	}
	return (count);
}

void	ft_fill_args_var_not_exist(char	**args, int *i)
{
	args[*i] = malloc(sizeof(char) * 2);
	args[*i][0] = '\0';
	args[*i][1] = '\0';
	*i += 1;
}

void	ft_fill_args_join(char **args, char *temp, int *i, int *j)
{
	char	*temp1;

	temp1 = args[*i];
	if (temp != NULL)
	{
		args[*i] = ft_strjoin(temp1, temp);
		free(temp1);
	}
	free(temp);
	*j += 1;
}

char	**ft_fill_args_finita(char **args, int i)
{
	args[i] = (void *)0;
	return (args);
}

char	**ft_fill_args(t_token *tok, int j, char **env, int ret)
{
	char	**args;
	int		i;

	i = 0;
	do_var_existe(&tok, tok[0].size, env, j);
	args = malloc(sizeof(char *) * (tok[0].size + 1));
	if (args == (void *)0)
		return ((void *)0);
	while (j < tok[0].size && tok[j].type != PIPE)
	{
		if (tok[j].type >= RED_OUT && tok[j].type <= RED_HERE_DOC)
			j++;
		else if (ft_fill_args_check_var_not_exist(tok, j))
			ft_fill_args_var_not_exist(args, &i);
		else if (ft_fill_args_check_expand(tok, j))
		{
			args[i] = ft_exp_dol(tok[j].value, tok[j].fl_q, env, ret);
			while (ft_fill_args_check_spaces(tok, j))
				ft_fill_args_join(args, ft_exp_dol(tok[j + 1].value,
						tok[j + 1].fl_q, env, ret), &i, &j);
			i++;
		}
		j++;
	}
	return (ft_fill_args_finita(args, i));
}
