/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 10:59:33 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/16 11:06:21 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	onec_exec(t_simple_command *c_table)
{
	if (ft_isbuiltin(c_table->cmd))
		ft_split_builtin(&c_table);
	else
		ft_exec_bin(c_table, c_table->env);
	return (c_table->last_ret);
}

pid_t	*init_childs(int nbr_sent)
{
	pid_t	*childs;

	childs = malloc(sizeof(pid_t) * nbr_sent);
	if (childs == NULL)
	{
		perror("minishell: malloc");
		return (NULL);
	}
	return (childs);
}

int	*init_pipes(int nbr_sent, pid_t *childs)
{
	int	i;
	int	*pipefd;

	i = 0;
	pipefd = malloc(sizeof(int) * nbr_sent * 2);
	if (pipefd == NULL)
	{
		perror("minishell: malloc");
		free(childs);
		return (NULL);
	}
	while (i < nbr_sent)
	{
		if (pipe(pipefd + i * 2) < 0)
		{
			perror("minishell: pipe");
			return (NULL);
		}
		i++;
	}
	return (pipefd);
}

void	dup_fds(int *pipefd, int i, t_simple_command *c_table, int size)
{
	if (i != 0)
	{
		if (dup2(pipefd[i - 2], STDIN_FILENO) < 0)
		{
			perror("minishell: dup4");
			close_pipes(pipefd, size);
			exit(1);
		}
	}
	if (c_table->next != NULL)
	{
		if (dup2(pipefd[i + 1], STDOUT_FILENO) < 0)
		{
			perror("minishell: dup3");
			close_pipes(pipefd, size);
			exit(1);
		}
	}
	close_pipes(pipefd, size);
}

void	launch_exec(t_simple_command *c_table, pid_t *childs,
			int *pipefd, int size)
{
	int	i;

	i = 0;
	while (c_table)
	{
		childs[i / 2] = fork();
		if (childs[i / 2] < 0)
			return (perror("minishell: fork"));
		if (childs[i / 2] == 0)
		{
			dup_fds(pipefd, i, c_table, size);
			if (ft_isbuiltin(c_table->cmd))
			{
				ft_split_builtin(&c_table);
				exit(free_one_memb(c_table, childs, pipefd, c_table->last_ret));
			}
			else if (c_table->args_num)
				ft_bin_nofork(c_table, c_table->env);
			exit(free_one_memb(c_table, childs, pipefd, c_table->last_ret));
		}
		else if (childs[i / 2] > 0)
			set_signals2();
		i += 2;
		c_table = c_table->next;
	}
}
