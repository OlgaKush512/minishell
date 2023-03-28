/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/16 11:05:06 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_lstcmd(t_simple_command *list)
{
	int	i;

	i = 0;
	while (list)
	{
		list->pos = i;
		i++;
		list = list->next;
	}
	return (i);
}

void	close_pipes(int *tab, int size)
{
	int	i;

	i = 0;
	while (i < size * 2)
		close(tab[i++]);
}

void	ft_add_prev(t_simple_command *c_table)
{
	t_simple_command	*start;

	start = c_table;
	while (c_table->next)
	{
		c_table->next->previous = c_table;
		c_table = c_table->next;
	}
	start->previous = NULL;
}

int	free_one_memb(t_simple_command *c_table, pid_t *tab, int *pipes, int ret)
{
	t_simple_command	*temp;

	c_table = get_first(c_table);
	temp = c_table;
	if (c_table->env)
		ft_free_2dstr(c_table->env);
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
	free_tab_pipes(tab, pipes);
	return (ret);
}

int	ft_pipe(t_simple_command *c_table)
{
	pid_t	*childs;
	int		*pipefd;
	int		nbr_sent;
	int		status;
	int		i;

	ft_add_prev(c_table);
	if (c_table->next == NULL)
		return (onec_exec(c_table));
	nbr_sent = ft_lstcmd(c_table);
	childs = init_childs(nbr_sent);
	if (childs)
		pipefd = init_pipes(nbr_sent, childs);
	ft_add_prev(c_table);
	if (childs == NULL || pipefd == NULL)
		return (1);
	launch_exec(c_table, childs, pipefd, nbr_sent);
	close_pipes(pipefd, nbr_sent);
	free(pipefd);
	i = 0;
	while (i < nbr_sent)
		waitpid(childs[i++], &status, 0);
	free(childs);
	return (WEXITSTATUS(status));
}
