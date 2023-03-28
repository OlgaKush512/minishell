/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   malloc_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 11:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/21 12:14:52 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_alltok(t_token *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		if (tab[i].type > RED_OUT)
			free(tab[i].value);
		i++;
	}
}

void	ft_check_nullarg(t_simple_command *lst, t_token *arr_tok, int size)
{
	t_simple_command	*start;

	start = lst;
	while (lst)
	{
		if ((!lst->args || !lst->cmd || !lst->env) && lst->err == 1)
		{
			ft_proper_free(start, start->env);
			free_alltok(arr_tok, size);
			write(2, "Error with malloc, exiting minishell..\n", 40);
			exit(1);
		}
		lst = lst->next;
	}
	ft_free_arrtok(arr_tok, size);
}

char	*add_arr_zer(char *arr, int i)
{
	arr[i] = 0;
	return (arr);
}
