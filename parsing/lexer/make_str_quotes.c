/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str_quotes.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:22 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/09 15:17:29 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	make_str_s_quotes(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] == '\'' && str[*i + 1] != '\'')
	{
		my_arr[*y].fl_q = 1;
		my_arr[*y].value = make_str(&str[*i], 1);
		my_arr[*y].fl_space = 0;
		*i = *i + 1;
		while (str[*i] != '\'' && str[*i])
			*i = *i + 1;
		if (str[*i] && str[*i] == '\'')
			*i = *i + 1;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
	}
	else if (str[*i] == '\'' && str[*i + 1] == '\'')
	{
		my_arr[*y].value = make_str(&str[*i], 1);
		*i = *i + 2;
		my_arr[*y].fl_q = 1;
		my_arr[*y].fl_space = 0;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
	}
}

void	check_str_double_quote(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i + 1] != '$')
	{
		my_arr[*y].fl_q = 2;
		my_arr[*y].value = make_str(&str[*i], 2);
		my_arr[*y].fl_q = 2;
		my_arr[*y].fl_space = 0;
		*y = *y + 1;
		*i = *i + 1;
	}
	else
	{
		my_arr[*y].fl_q = 2;
		*i = *i + 1;
	}
}

void	make_str_double_quote_filled(char *str, t_token *my_arr, int *i, int *y)
{
	check_str_double_quote(str, my_arr, i, y);
	while (str[*i] && str[*i] != '\0' && str[*i] != '"')
	{
		while (str[*i] != '\0' && str[*i] != '"' && str[*i] != '$')
			*i = *i + 1;
		if (str[*i] == '$')
			my_arr[*y].fl_q = 2;
		make_str_dollar(str, my_arr, i, y);
		if (str[*i] != '\0' && str[*i] != '\"' && str[*i] != '$')
		{
			my_arr[*y].fl_space = 0;
			my_arr[*y].fl_q = 2;
			my_arr[*y].value = make_str(&str[*i], my_arr[*y].fl_q);
			*y = *y + 1;
		}
	}
	if (str[*i] == '"')
		*i = *i + 1;
	if (str[*i] == ' ')
		my_arr[*y - 1].fl_space = 1;
}

void	make_str_double_quote(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] == '"' && str[*i + 1] != '"')
		make_str_double_quote_filled(str, my_arr, i, y);
	else if (str[*i] == '"' && str[*i + 1] == '"')
	{
		my_arr[*y].value = make_str(&str[*i], 2);
		*i = *i + 2;
		my_arr[*y].fl_q = 2;
		my_arr[*y].fl_space = 0;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
	}
}

void	make_str_dq_cons(char *arr, char *str, int *i, int len)
{
	while (*i < len)
	{
		arr[*i] = str[*i];
		*i += 1;
	}
}
