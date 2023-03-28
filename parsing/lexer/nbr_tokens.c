/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nbr_tokens.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 15:17:44 by okushnir          #+#    #+#             */
/*   Updated: 2021/12/23 10:53:13 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	nbr_words_dollar_body(char const *str, int *i)
{
	if (str[*i] && ((str[*i] == '"' && str[*i + 1] == '"')
			|| (str[*i] == '\'' && str[*i + 1] == '\'')))
		*i = *i + 2;
	else if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
			&& str[*i] != '$') && (!in_charset(str[*i]))
		&& (str[*i] == '_' || ft_isalpha(str[*i])))
	{
		*i = *i + 1;
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"'
				&& str[*i] != '$') && (!in_charset(str[*i]))
			&& (str[*i] == '_' || ft_isalpha(str[*i])
				|| ft_isdigit(str[*i])))
			*i = *i + 1;
	}
	else if (str[*i] && str[*i] == '$')
		*i = *i + 1;
	else if (str[*i] && (str[*i] != '\'' && str[*i] != '"'
			&& str[*i] != '$') && (!in_charset(str[*i])))
		*i = *i + 1;
}

int	nbr_words_dollar(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '$')
	{
		words++;
		*i = *i + 1;
		if (str[*i] != '<' && str[*i] != '>')
			nbr_words_dollar_body(str, i);
	}
	return (words);
}

int	nbr_words_redir(char const *str, int *i)
{
	int	words;

	words = 0;
	if (str[*i] == '>')
	{
		words++;
		*i = *i + 1;
		if (str[*i] == '>')
			*i = *i + 1;
	}
	else if (str[*i] == '<')
	{
		words++;
		*i = *i + 1;
		if (str[*i] == '<')
			*i = *i + 1;
	}
	else if (str[*i] == '|')
	{
		words++;
		*i = *i + 1;
	}
	return (words);
}

int	nbr_words_simple(char const *str, int *i)
{
	int	words;

	words = 0;
	if ((str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i])))
		*i = *i + 1;
	if (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
		&& (in_charset(str[*i]) == 0) && str[*i] != '>'
		&& str[*i] != '<' && str[*i] != '|')
	{
		words++;
		while (str[*i] && (str[*i] != '\'' && str[*i] != '"' && str[*i] != '$')
			&& (!in_charset(str[*i])) && str[*i] != '>'
			&& str[*i] != '<' && str[*i] != '|' )
			*i = *i + 1;
	}
	return (words);
}

int	nbr_words(char const *str)
{
	int	words;
	int	i;
	int	len;
	int	check;

	words = 0;
	i = 0;
	check = 0;
	len = (int)ft_strlen(str);
	while ((i < len) && str[i])
	{
		words += nbr_words_simple(str, &i);
		words += nbr_words_dollar(str, &i);
		words += nbr_words_redir(str, &i);
		check = nbr_words_s_quotes(str, &i);
		if (check < 0)
			return (check);
		words += check;
		check = nbr_words_double_quotes(str, &i);
		if (check < 0)
			return (check);
		words += check;
	}
	return (words);
}
