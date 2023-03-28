/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/25 13:42:23 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/23 10:56:53 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

char	*add_index_file(char *str, int pos)
{
	char	*index;
	char	*res;

	index = ft_itoa(pos);
	res = ft_strjoin(str, index);
	free(index);
	return (res);
}

void	ft_write_wfolder(t_redir *wrong, t_simple_command *c_table)
{
	if (wrong->type == 0)
		ft_add_output(wrong->file, c_table);
	else if (wrong->type == 1)
		ft_add_input(wrong->file, c_table);
	else if (wrong->type == 2)
		ft_add_append(wrong->file, c_table);
	write(2, "minishell: ", 12);
	write(2, wrong->file, ft_strlen(wrong->file));
	write(2, ": ", 2);
	if (c_table->badfd == 1)
		write(2, "Is a folder\n", 13);
	else
		perror(NULL);
}

void	ft_file_error(t_simple_command *c_table)
{
	if (c_table->infile >= 0)
		close(c_table->infile);
	c_table->infile = -42000;
	if (c_table->outfile >= 0)
		close (c_table->outfile);
	c_table->outfile = -42000;
}

int	ft_isfolder(char *file, int ret)
{
	int		bytes;
	char	buff[10];

	bytes = read(ret, buff, 1);
	close (ret);
	if (bytes < 0)
		return (0);
	bytes = open(file, O_RDONLY);
	if (bytes < 0)
		return (0);
	return (1);
}

void	write_heredoc(char *delim, int ret, char **env)
{
	char		*str;
	extern int	g_signum;

	while (1)
	{
		str = readline("> ");
		if (g_signum == 130)
			return ;
		if (str == NULL)
		{
			write(2, "minishell: warning: \"heredoc\"", 30);
			write(2, " closed by EOF (instead of \" ", 30);
			write(2, delim, ft_strlen(delim));
			write(2, " \")\n", 5);
			return ;
		}
		if (strcmp(str, delim) == 0)
		{
			free(str);
			return ;
		}
		write_exp_heredoc(str, env, ret);
		write(ret, "\n", 1);
		free(str);
	}
}
