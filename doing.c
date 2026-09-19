/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doing.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabarak <tabarak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/15 21:49:09 by tabarak           #+#    #+#             */
/*   Updated: 2026/02/27 23:35:32 by tabarak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	is_thinking(t_philo *philo)
{
	protect_printing(philo, "is thinking");
	philo_odd_waitiig(philo);
	philo_even_wating(philo);
}

void	is_sleeping(t_philo *philo)
{
	protect_printing(philo, "is sleeping");
	sleeping(philo->data->time->time_to_sleep);
}

void	is_eating(t_philo *philo)
{
	if (philo->philo_id % 2 == 0)
	{
		if (philo_even(philo))
			return ;
	}
	else
	{
		if (philo_odd(philo))
			return ;
	}
	protect_printing(philo, "is eating");
	protect_timing(philo);
	sleeping(philo->data->time->time_to_eat);
	pthread_mutex_unlock(&philo->right->fork);
	pthread_mutex_unlock(&philo->left->fork);
	pthread_mutex_lock(&philo->data->meals_moitor);
	philo->meals++;
	pthread_mutex_unlock(&philo->data->meals_moitor);
	if (!checking_num_of_meals(philo))
		return ;
}

int	checking_num_of_meals(t_philo *philo)
{
	if (philo->data->number_must_eat == -1)
		return (1);
	pthread_mutex_lock(&philo->data->monitor_num_of_meals);
	if (philo->meals >= philo->data->number_must_eat)
	{
		philo->stop = 1;
		pthread_mutex_unlock(&philo->data->monitor_num_of_meals);
		return (0);
	}
	pthread_mutex_unlock(&philo->data->monitor_num_of_meals);
	return (1);
}
