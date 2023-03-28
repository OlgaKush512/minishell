/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   what_is_len.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: okushnir <okushnir@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:18:03 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/09 15:18:06 by okushnir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	what_is_len_s_quotes(char *str)
{
	int	len;

	len = 0;
	if (*str == '\'' && *(str + 1) == '\'')
		len++;
	else
	{
		str++;
		while (*str && *str != '\'')
		{
			len++;
			str++;
		}
	}
	return (len);
}

int	what_is_len_double_quotes(char *str)
{
	int	len;

	len = 0;
	if (*str == '\'' && *(str + 1) == '\'')
		len++;
	else if (*str == '"' && *(str + 1) != '"')
	{
		str++;
		while (*str && *str != '"' && *str != '$')
		{
			len++;
			str++;
		}
	}
	else
	{
		str++;
		len++;
		while (*str && *str != '"' && *str != '$')
		{
			len++;
			str++;
		}
	}
	return (len);
}

int	what_is_len_simple(char *str)
{
	int	len;

	len = 0;
	while (*str != '\0' && (*str != '\'' && *str != '"' && *str != '$')
		&& (!in_charset(*str)) && *str != '>' && *str != '<' && *str != '|')
	{
		len++;
		str++;
	}
	return (len);
}

int	what_is_len_dollar_var(char *str)
{
	int	len;

	len = 0;
	len++;
	str++;
	while (*str && (*str == '_' || ft_isalpha(*str) || ft_isdigit(*str)))
	{
		len++;
		str++;
	}
	return (len);
}

int	what_is_len_dollar(char *str)
{
	int	len;

	len = 1;
	str++;
	if (*str && ((*str == '"' && *(str + 1) == '"')
			|| (*str == '\'' && *(str + 1) == '\'')))
		len += 2;
	else if (*str && (*str == '<' || *str == '>' || *str == ' '))
		return (len);
	else if (*str && ((*str == '"' && *(str + 1) != '"' && *(str - 2) != '"')
			|| (*str == '\'' && *(str + 1) != '\'' && *(str - 2) != '\'')))
		len += 1;
	else if (*str && *str == '$')
		len++;
	else if (*str && *str == '?')
		len++;
	else if (*str && (*str != '\'' && *str != '"'
			&& *str != '$') && (!in_charset(*str))
		&& *str != '_' && !ft_isalpha(*str))
		len++;
	else if (*str && (*str == '_' || ft_isalpha(*str)))
		len += what_is_len_dollar_var(str);
	return (len);
}
