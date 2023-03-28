/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_tokens.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:16:57 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/23 10:52:57 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	what_is_len(char *str, int fl_q)
{
	int		i;
	char	*arr;

	i = 0;
	arr = str;
	if (*arr == '\0')
		return (0);
	if (*arr == '\'' && fl_q == 1)
		i = what_is_len_s_quotes(str);
	else if ((*arr == '"' || fl_q == 2) && *arr != '$')
		i = what_is_len_double_quotes(arr);
	else if (*arr != '$' && (*arr != '<' && *arr != '>' && *arr != '|'))
		i = what_is_len_simple(arr);
	else if (*arr == '$')
		i = what_is_len_dollar(arr);
	else if (*arr == '<' || *arr == '>' || *arr == '|')
		i = what_is_len_redir(arr);
	else
	{
		i++;
		arr++;
		if (*arr != '\0' && *arr != '$')
			i += what_is_len_simple(arr);
	}
	return (i);
}

void	make_str_body(char *arr, char *str, int *i, int len)
{
	if (str[*i] && ((str[*i + 1] == '"' && str[*i + 2] == '"')
			|| (str[*i + 1] == '\'' && str[*i + 2] == '\'')))
	{
		while (*i < len)
		{
			arr[*i] = str[*i];
			*i += 1;
		}
	}
	else
	{
		while (*i < len && str[*i] != '"' && str[*i] != '\'')
		{
			arr[*i] = str[*i];
			*i += 1;
		}
		if (str[*i] == '"' || str[*i] == '\'')
		{
			while (*i < len)
			{
				arr[*i] = ' ';
				*i += 1;
			}	
		}
	}
}

int	make_str_check(char *arr, char **str, int *i, int fl_q)
{
	if (**str == '\'' && *(*str + 1) == '\'')
	{
		arr[*i] = '\0';
		return (0);
	}
	else if (**str == '"' && *(*str + 1) == '"')
	{
		arr[*i] = '\0';
		return (0);
	}
	else if (**str == '\'' && *(*str + 1) != '\'' && fl_q != 2)
		*str = *str + 1;
	else if (**str == '"' && *(*str + 1) != '"')
		*str = *str + 1;
	return (1);
}

char	*make_str(char *str, int fl_q)
{
	int		i;
	char	*arr;
	int		len;

	i = 0;
	len = what_is_len(str, fl_q);
	arr = (char *)malloc(sizeof(char) * (len + 1));
	if (!arr)
		return (NULL);
	make_str_body_two(str, arr, &i, fl_q);
	if (make_str_check(arr, &str, &i, fl_q))
	{
		if (*str == '"' && fl_q != 2)
			make_str_dq_cons(arr, str, &i, len);
		else if (fl_q != 2)
			make_str_body(arr, str, &i, len);
		else
		{
			i--;
			while (++i < len && str[i] != '"')
				arr[i] = str[i];
		}
	}
	return (add_arr_zer(arr, i));
}

t_token	*ft_split_tokens(char *str, int nbr_tokens)
{
	t_token	*my_arr;
	int		i;
	int		y;

	if (!str)
		return (malloc(0));
	y = 0;
	i = 0;
	my_arr = (t_token *)malloc(sizeof(t_token) * (nbr_tokens + 1));
	if (my_arr == (void *)0)
		return ((void *)0);
	while (i < ft_strlen(str) && str[i])
	{
		make_str_simple(str, my_arr, &i, &y);
		make_str_redir(str, my_arr, &i, &y);
		if (str[i] == '$')
			my_arr[y].fl_q = 0;
		make_str_dollar(str, my_arr, &i, &y);
		make_str_s_quotes(str, my_arr, &i, &y);
		make_str_double_quote(str, my_arr, &i, &y);
	}
	i = 0;
	fill_size_tokens(my_arr, nbr_tokens);
	typification(my_arr, nbr_tokens);
	return (my_arr);
}
