/* ************************************************************************** */
/*	                                                                          */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/11/25 13:35:14 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "../libft/libft.h"

int	check_tty(void)
{
	if (isatty(STDIN_FILENO) == 0)
	{
		write(2, "can't read from a file, exiting.. \n", 36);
		exit (1);
	}
	return (0);
}

int	check_exec(int mode, t_simple_command *c_table)
{
	if (c_table->args[0] != 0 && (mode != 0
			|| ft_strncmp(c_table->args[0], "./", 2) == 0
			|| c_table->args[0][0] == '/'))
		return (1);
	return (0);
}

void	ft_del_heredoc(int index)
{
	char	*ind;
	char	*file;

	ind = ft_itoa(index);
	file = ft_strjoin("file/.heredoc", ind);
	unlink(file);
	free(ind);
	free(file);
}

void	ft_free_2dstr(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		str[i] = NULL;
		i++;
	}
	free(str);
	str = NULL;
}

int	ft_proper_free(t_simple_command *c_table, char **env)
{
	t_simple_command	*temp;

	if (c_table == NULL)
		return (0);
	if (env)
		ft_free_2dstr(env);
	temp = c_table;
	while (c_table)
	{
		temp = c_table;
		if (c_table->args)
			ft_free_2dstr(c_table->args);
		if (c_table->redir)
			ft_free_redir(&(c_table->redir));
		if (c_table->infile >= 0)
			close(c_table->infile);
		if (c_table->outfile >= 0)
			close(c_table->outfile);
		ft_del_heredoc(c_table->pos);
		c_table = c_table->next;
		free(temp);
	}
	return (1);
}
