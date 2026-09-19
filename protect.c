/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   protect.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabarak <tabarak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:40:46 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/27 23:07:11 by tabarak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	protect_timing(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->monitor_timing);
	philo->time_start_eating = time_right_now();
	pthread_mutex_unlock(&philo->data->monitor_timing);
}

void	protect_printing(t_philo *philo, char *message)
{
	pthread_mutex_lock(&philo->data->printing);
	pthread_mutex_lock(&philo->data->monitor);
	if (!philo->data->is_someone_died)
		printf("%ld %d %s\n", time_right_now() - philo->data->start_eating,
			philo->philo_id, message);
	pthread_mutex_unlock(&philo->data->monitor);
	pthread_mutex_unlock(&philo->data->printing);
}

int	philo_odd(t_philo *philo)
{
	pthread_mutex_lock(&philo->right->fork);
	protect_printing(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->monitor);
	if (philo->data->is_someone_died)
	{
		pthread_mutex_unlock(&philo->data->monitor);
		pthread_mutex_unlock(&philo->right->fork);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->monitor);
	pthread_mutex_lock(&philo->left->fork);
	protect_printing(philo, "has taken a fork");
	return (0);
}

int	philo_even(t_philo *philo)
{
	pthread_mutex_lock(&philo->left->fork);
	protect_printing(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->monitor);
	if (philo->data->is_someone_died)
	{
		pthread_mutex_unlock(&philo->left->fork);
		pthread_mutex_unlock(&philo->data->monitor);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->monitor);
	pthread_mutex_lock(&philo->right->fork);
	protect_printing(philo, "has taken a fork");
	return (0);
}
