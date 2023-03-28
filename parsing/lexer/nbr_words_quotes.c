/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_words_quotes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:54 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/10 11:27:54 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	nbr_words_s_quotes(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '\'' && str[*i + 1] != '\'')
	{
		words++;
		*i = *i + 1;
		while (str[*i] != '\'' && str[*i])
			*i = *i + 1;
		if (str[*i] && str[*i] == '\'')
			*i = *i + 1;
		else if (str[*i] == 0)
		{
			write(2, "Error: There is not second single quotes\n", 42);
			return (-1);
		}
	}
	else if (str[*i] == '\'' && str[*i + 1] == '\'')
	{
		words++;
		*i = *i + 2;
	}
	return (words);
}

int	mouve_index(char const *str, int *i)
{
	int	words;

	words = 0;
	while (str[*i] && str[*i] != '"')
	{
		while (str[*i] && str[*i] != '"' && str[*i] != '$')
			*i = *i + 1;
		words += nbr_words_dollar(str, i);
		if (str[*i] != '\"' && str[*i] != '$')
			words++;
	}
	return (words);
}

int	nbr_words_double_quotes(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '"')
	{
		*i = *i + 1;
		if (str[*i] != '\"' && str[*i] != '$')
			words++;
		words += mouve_index(str, i);
		if (str[*i] == '"' && str[*i - 1] == '"')
		{
			words++;
			*i = *i + 1;
		}
		else if (str[*i] == '"' && str[*i - 1] != '"')
			*i = *i + 1;
		else
		{
			write(2, "Error: There is not second double quotes\n", 42);
			return (-2);
		}
	}
	return (words);
}

int	in_charset(char letter)
{
	if (letter == ' ' || letter == '\t' || letter == '\n')
		return (1);
	return (0);
}

int	what_is_len_redir(char *str)
{
	int	len;

	len = 0;
	if (*str == '>')
	{
		len++;
		str++;
		if (*str == '>')
			len++;
	}
	else if (*str == '<')
	{
		len++;
		str++;
		if (*str == '<')
			len++;
	}
	else if (*str == '|')
		len++;
	return (len);
}
