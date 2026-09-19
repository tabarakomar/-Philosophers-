/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talshoub <talshoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:16:02 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/28 15:11:29 by talshoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_if_num(char *argv)
{
	int	i;

	i = 0;
	if (!argv || argv[0] == '\0')
		return (0);
	while (argv[i])
	{
		if (argv[i] == '+' || argv[i] == '-')
		{
			i++;
			if (!argv[i])
				return (0);
		}
		if (!(argv[i] >= '0' && argv[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

int	checking_argument(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (!check_if_num(argv[i]))
		{
			write(2, "the input is not a num\n", 23);
			return (0);
		}
		if ((ft_atoi(argv[i]) <= 0) || !(anatoi(argv[i])))
		{
			write(2, "The Input Is Out Of Rang\n", 25);
			return (0);
		}
		i++;
	}
	return (1);
}
