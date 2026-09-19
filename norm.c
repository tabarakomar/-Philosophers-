/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   norm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: talshoub <talshoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/21 16:27:56 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/21 16:45:36 by talshoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	meals_done_norm(t_data *input)
{
	if (meals_done(input))
	{
		pthread_mutex_lock(&input->monitor);
		input->is_someone_died = 1;
		pthread_mutex_unlock(&input->monitor);
		return (0);
	}
	return (1);
}

void	protect_timing_norm(t_philo *philo, long *time_now,
		long *time_of_last_meal)
{
	pthread_mutex_lock(&philo->data->monitor_timing);
	*time_now = time_right_now();
	*time_of_last_meal = philo->time_start_eating;
	pthread_mutex_unlock(&philo->data->monitor_timing);
}

void	protect_print_death(t_data *input, int i)
{
	pthread_mutex_lock(&input->printing);
	printf("%ld %d died\n", time_right_now() - input->start_eating,
		input->philo[i].philo_id);
	pthread_mutex_unlock(&input->printing);
}

void	locking_death(t_data *input)
{
	pthread_mutex_lock(&input->monitor);
	input->is_someone_died = 1;
	pthread_mutex_unlock(&input->monitor);
}

int	nor_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->monitor);
	if (philo->data->is_someone_died == 1 || philo->stop == 1)
	{
		pthread_mutex_unlock(&philo->data->monitor);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->monitor);
	return (0);
}
