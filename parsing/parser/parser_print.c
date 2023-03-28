/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_print.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 14:57:26 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/10 11:10:08 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_args(t_simple_command *start)
{
	int	i;

	i = 0;
	printf("ARGS : ");
	while (start->args[i])
	{
		printf("%s\t", start->args[i++]);
	}
	printf("\n");
}

void	print_redir(t_simple_command *c)
{
	t_redir	*save;

	save = c->redir;
	printf("REDIR : 0 = out    1 = in    2 = out_append    3 = here_doc\n");
	while (c->redir)
	{
		printf("type : %d  vers file : %s\t", c->redir->type, c->redir->file);
		c->redir = c->redir->next;
	}
	printf("\n\n");
	c->redir = save;
}

void	ft_print_sentences(t_simple_command *start)
{
	int	i;

	i = 0;
	while (start)
	{
		printf("SENTENCE : %d\n\n", i++);
		printf("COMMANDE : %s\n", start->cmd);
		print_args(start);
		print_redir(start);
		printf("index : %d\n", start->pos);
		start = start->next;
	}
}
