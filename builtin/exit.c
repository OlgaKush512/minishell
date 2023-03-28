/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 11:00:52 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/10 16:53:59 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[0] == '-')
		i = 1;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

void	exit_too_long(t_simple_command *c_table)
{
	if (c_table->pos == 0 && c_table->next == NULL)
		write(1, "exit\n", 5);
	write(2, "minishell: exit: ", 18);
	write(2, c_table->args[1], ft_strlen(c_table->args[1]));
	write(2, ": numeric argument required\n", 29);
	ft_proper_free(c_table, c_table->env);
	exit(2);
}

int	ft_exitreturn(char *str)
{
	long long int	res;
	int				neg;
	int				i;

	if (!str)
		return (-1);
	neg = 1;
	res = 0;
	if (check_number(str) == 1)
		return (-420);
	i = 0;
	if (str[0] == '-')
	{
		neg = -1;
		i = 1;
	}
	while (str[i])
	{
		res = res * 10 + (str[i] - '0');
		i++;
	}
	return ((res * neg) % 256);
}

void	ft_bi_exit(t_simple_command *c_table)
{
	int	ret;

	ret = ft_exitreturn(c_table->args[1]);
	if (c_table->args_num == 1)
	{		
		ret = c_table->last_ret;
		if (c_table->pos == 0 && c_table->next == NULL)
			write(1, "exit\n", 5);
		ft_proper_free(c_table, c_table->env);
		exit(ret);
	}
	else if (ret == -420)
		exit_too_long(c_table);
	else if (c_table->args_num > 2)
	{
		write(2, "exit\nminishell: exit: too many arguments\n", 42);
		c_table->last_ret = 1;
	}
	else
	{
		if (c_table->pos == 0 && c_table->next == NULL)
			write(1, "exit\n", 5);
		ft_proper_free(c_table, c_table->env);
		exit(ret);
	}
}
