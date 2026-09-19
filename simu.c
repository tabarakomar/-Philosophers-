/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simu.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabarak <tabarak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:44:51 by tabarak           #+#    #+#             */
/*   Updated: 2026/02/27 23:28:36 by tabarak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*handel_thread(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->data->number_of_philo == 1)
	{
		protect_printing(philo, "is thinking");
		protect_printing(philo, "has taken a fork");
		usleep(philo->data->time->time_to_eat);
		return (NULL);
	}
	while (1)
	{
		if (nor_check(philo))
			return (NULL);
		is_thinking(philo);
		is_eating(philo);
		if (philo->stop == 1)
			return (NULL);
		is_sleeping(philo);
	}
	return (NULL);
}

void	init_thread_joing(t_philo *philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join(philo[i].num_p, NULL);
		i++;
	}
}

int	checking_death(long time_to_die, long time_now, long time_of_last_meal)
{
	long	a;

	a = time_now - time_of_last_meal;
	if (a >= time_to_die)
		return (1);
	return (0);
}

int	meals_done(t_data *input)
{
	int	i;

	i = 0;
	if (input->number_must_eat == -1)
		return (0);
	while (i < input->number_of_philo)
	{
		pthread_mutex_lock(&input->meals_moitor);
		if (input->philo[i].meals < input->number_must_eat)
		{
			pthread_mutex_unlock(&input->meals_moitor);
			return (0);
		}
		pthread_mutex_unlock(&input->meals_moitor);
		i++;
	}
	return (1);
}

void	is_death(t_data *input, int n)
{
	int		i;
	long	time_now;
	long	time_of_last_meal;

	while (1)
	{
		if (!meals_done_norm(input))
			return ;
		i = 0;
		while (i < n)
		{
			protect_timing_norm(&input->philo[i], &time_now,
				&time_of_last_meal);
			if (checking_death(input->time->time_to_die, time_now,
					time_of_last_meal))
			{
				locking_death(input);
				protect_print_death(input, i);
				return ;
			}
			i++;
		}
		usleep(600);
	}
}
