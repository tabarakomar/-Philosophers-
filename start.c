/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabarak <tabarak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/10 10:38:36 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/27 23:34:18 by tabarak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start(t_data **input, char **argv)
{
	(*input)->number_of_philo = ft_atoi(argv[1]);
	(*input)->number_of_fork = ft_atoi(argv[1]);
	(*input)->time->time_to_die = ft_atoi(argv[2]);
	(*input)->time->time_to_eat = ft_atoi(argv[3]);
	(*input)->time->time_to_sleep = ft_atoi(argv[4]);
	(*input)->is_someone_died = 0;
	(*input)->start_eating = time_right_now();
	if (argv[5] != NULL)
	{
		(*input)->number_must_eat = ft_atoi(argv[5]);
		if (pthread_mutex_init(&(*input)->monitor_num_of_meals, NULL) != 0)
		{
			write(2, "cannt init mutex\n", 17);
			pthread_mutex_destroy(&(*input)->monitor_num_of_meals);
			return ;
		}
	}
	else
		(*input)->number_must_eat = -1;
}

int	initilize(t_data **input, char **argv, t_fork **fork, t_philo **philo)
{
	start(input, argv);
	init_mutex(input);
	if (!init_fork((*input)->number_of_philo, fork))
		return (0);
	(*input)->fork = *fork;
	if (!(init_philo(philo, (*input)->number_of_philo, fork, *input)))
		return (0);
	return (1);
}

void	simulation(t_data *input)
{
	init_thread(&input->philo, input->number_of_philo);
	is_death(input, input->number_of_philo);
	init_thread_joing(input->philo, input->number_of_philo);
}

void	philo_odd_waitiig(t_philo *philo)
{
	if (philo->philo_id % 2 != 0 && philo->meals == 0)
		sleeping(philo->data->time->time_to_eat / 2);
}

void	philo_even_wating(t_philo *philo)
{
	if (philo->data->number_of_philo % 2 != 0 && philo->philo_id % 2 == 0
		&& philo->meals > 0)
		sleeping(philo->data->time->time_to_eat / 2);
}
