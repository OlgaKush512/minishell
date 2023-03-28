/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_str_simple_dollar_redir.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:36 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/23 10:54:13 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	make_str_dollar_filled(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
			&& str[*i] != '$') && (!in_charset(str[*i]))
		&& (str[*i] == '_' || ft_isalpha(str[*i])))
	{
		*i = *i + 1;
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"'
				&& str[*i] != '$') && (!in_charset(str[*i]))
			&& (str[*i] == '_' || ft_isalpha(str[*i]) || ft_isdigit(str[*i])))
			*i = *i + 1;
	}
	else if (str[*i] && ((str[*i] != '<') && (str[*i] != '>')))
		*i = *i + 1;
	if (str[*i] == ' ' && my_arr[*y].fl_q != 2)
		my_arr[*y].fl_space = 1;
}

void	make_str_dollar(char *str, t_token *my_arr, int *i, int *y)
{
	if (str[*i] == '$')
	{
		my_arr[*y].value = make_str(&str[*i], my_arr[*y].fl_q);
		if (str[*i + 1] != ' ' || my_arr[*y].fl_q != 2)
			*i = *i + 1;
		my_arr[*y].fl_space = 0;
		if (str[*i] && ((str[*i] == '"' && str[*i + 1] == '"')
				|| (str[*i] == '\'' && str[*i + 1] == '\'')))
		{
			*i = *i + 2;
			if (str[*i] == ' ' && my_arr[*y].fl_q != 2)
				my_arr[*y].fl_space = 1;
		}			
		else if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
				&& str[*i] != '$'))
			make_str_dollar_filled(str, my_arr, i, y);
		else if (str[*i] && str[*i] == '$')
		{
			*i = *i + 1;
			if (str[*i] == ' ' && my_arr[*y].fl_q != 2)
				my_arr[*y].fl_space = 1;
		}
		*y = *y + 1;
	}
}

void	make_str_simple(char *str, t_token *my_arr, int *i, int *y)
{
	if ((str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i])))
		*i = *i + 1;
	if (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i]) == 0) && str[*i] != '>'
		&& str[*i] != '<' && str[*i] != '|')
	{
		my_arr[*y].value = make_str(&str[*i], 0);
		my_arr[*y].fl_q = 0;
		my_arr[*y].fl_space = 0;
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
			&& (!in_charset(str[*i])) && str[*i] != '>'
			&& str[*i] != '<' && str[*i] != '|')
			*i = *i + 1;
		if (str[*i] == ' ')
			my_arr[*y].fl_space = 1;
		*y = *y + 1;
	}
}

void	make_str_redir(char *str, t_token *my_arr, int *i, int *y)
{
	int	len;

	len = 0;
	if (str[*i] == '>' || str[*i] == '<')
	{
		len = what_is_len(&str[*i], 0);
		my_arr[*y].fl_q = 0;
		my_arr[*y].fl_space = 1;
		my_arr[*y].value = make_str(&str[*i], 0);
		*y = *y + 1;
		*i += len;
	}
	else if (str[*i] == '|')
	{
		my_arr[*y].fl_q = 0;
		my_arr[*y].fl_space = 1;
		my_arr[*y].value = make_str(&str[*i], 0);
		*y = *y + 1;
		*i = *i + 1;
	}
}

void	make_str_body_two(char *str, char *arr, int *i, int fl_q)
{
	int	len;

	len = what_is_len(str, fl_q);
	if (fl_q == 1)
	{
		if (make_str_check(arr, &str, i, fl_q))
		{
			while (*i < len)
			{
				arr[*i] = str[*i];
				*i = *i + 1;
			}
		}
	}
}
