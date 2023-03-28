/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   segfault.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbeaurai <cbeaurai@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 10:52:05 by cbeaurai          #+#    #+#             */
/*   Updated: 2021/12/23 10:52:00 by cbeaurai         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

// int	main(void)
// {
// 	kill(0, SIGSEGV);
// 	return (0);
// }

// int	main ()
// {
// 	char *str;
// 	str = malloc(sizeof(char) * 2);
// 	str[5] = 'r';
// 	printf("%s", str);
// 	return (0);
// }

// int  main(void)
// {
//     while (1)
//     {
//         write(2, "test", 5);
//     }
//     return (0);
// }