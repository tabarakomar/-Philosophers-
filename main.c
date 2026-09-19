/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talshoub <talshoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:12:18 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/28 15:01:26 by talshoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	first_step(int argc, char **argv)
{
	if (argc != 5)
	{
		if (argc != 6)
		{
			write(2, "Wrong argumnet\n", 15);
			return (0);
		}
	}
	if (!checking_argument(argv))
	{
		write(2, "Wrong argumnet\n", 15);
		return (0);
	}
	return (1);
}

void	free_things(t_data **input, t_time **times)
{
	free((*input)->fork);
	free((*input)->philo);
	free(*times);
	free(*input);
}

void	memset_fun_norm(t_time **times, t_data **input)
{
	memset(*times, 0, sizeof(t_time));
	memset(*input, 0, sizeof(t_data));
}

int	main(int argc, char **argv)
{
	t_data	*input;
	t_time	*times;
	t_philo	*philo;
	t_fork	*fork;

	if (!first_step(argc, argv))
		return (1);
	times = malloc(sizeof(*times));
	input = malloc(sizeof(t_data));
	if (!input || !times)
	{
		free(input);
		free(times);
		return (1);
	}
	memset_fun_norm(&times, &input);
	input->time = times;
	if (!(initilize(&input, argv, &fork, &philo)))
	{
		free_things(&input, &times);
		return (1);
	}
	simulation(input);
	free_things(&input, &times);
	return (0);
}
