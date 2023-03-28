/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   which_type_is_it.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:18:18 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/16 11:52:20 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] != '\0' && s1[i] == s2[i] && i < n - 1)
		i++;
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

int	which_type(t_token *my_arr)
{
	if (ft_strlen(my_arr->value) == 1 && *(my_arr->value) == '|'
		&& my_arr->fl_q == 0)
		return (PIPE);
	else if (ft_strlen(my_arr->value) == 1 && *(my_arr->value) == '>'
		&& my_arr->fl_q == 0)
		return (RED_OUT);
	else if (ft_strlen(my_arr->value) == 1 && *(my_arr->value) == '<'
		&& my_arr->fl_q == 0)
		return (RED_IN);
	else if (ft_strlen(my_arr->value) == 2
		&& (ft_strncmp(">>", my_arr->value, 2) == 0) && my_arr->fl_q == 0)
		return (RED_OUT_APP);
	else if (ft_strlen(my_arr->value) == 2
		&& (ft_strncmp("<<", my_arr->value, 2) == 0) && my_arr->fl_q == 0)
		return (RED_HERE_DOC);
	else if ((ft_strncmp("$", my_arr->value, 1) == 0) && my_arr->fl_q != 1
		&& ft_strlen(my_arr->value) != 1)
		return (DOLLAR);
	else
		return (ARG);
	return (0);
}

void	free_ttoken(t_token *tab, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		free(tab[i].value);
		i++;
	}
	write(2, "Error with malloc, exiting minishell\n", 38);
}

void	typification(t_token *my_arr, int nbr_token)
{
	int	i;

	i = 0;
	while (i < nbr_token)
	{
		if (my_arr[i].value == NULL)
		{
			free_ttoken(my_arr, nbr_token);
			exit(1);
		}
		my_arr[i].type = which_type(&(my_arr[i]));
		i++;
	}
}

void	fill_size_tokens(t_token *my_arr, int nbr_tokens)
{
	int	i;

	i = 0;
	while (i < nbr_tokens)
	{
		my_arr[i].size = nbr_tokens;
		i++;
	}
	my_arr[nbr_tokens].fl_q = -1;
}
