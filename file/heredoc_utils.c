/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 16:53:00 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/16 17:15:07 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	sizetochar(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

int	skip_expand(char *str)
{
	int	i;

	i = 2;
	if (ft_isalpha(str[1]) == 0 && str[1] != '_')
		return (1);
	while (ft_isalnum(str[i]) || str[i] == '_')
		i++;
	return (i);
}

char	*get_exp(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
		i++;
	if (str[i] == '=')
		i++;
	else
		return (NULL);
	return (ft_strdup(&str[i]));
}

char	*expended(char *str, char **env)
{
	int	len;
	int	i;
	int	len_env;

	i = 0;
	len = skip_expand(str);
	if (str[1] == 0)
		return (ft_strdup("$"));
	while (env[i])
	{
		len_env = skip_expand(env[i]);
		if (ft_strncmp(&str[1], env[i], len - 1) == 0
			&& ft_strncmp(&str[1], env[i], len_env) == 0)
			return (get_exp(env[i]));
		i++;
	}
	return (NULL);
}

void	write_exp_heredoc(char *str, char **env, int fd)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i])
	{
		write(fd, &str[i], sizetochar(&str[i], '$'));
		i += sizetochar(&str[i], '$');
		if (str[i] == '$')
		{
			temp = expended(&str[i], env);
			if (temp)
				write(fd, temp, ft_strlen(temp));
			free(temp);
			i += skip_expand(&str[i]);
		}
	}
}
