/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabarak <tabarak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/16 15:39:33 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/27 22:35:01 by tabarak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_mutex(t_data **input)
{
	if (pthread_mutex_init(&(*input)->monitor_timing, NULL) != 0)
	{
		write(2, "cannt init mutex\n", 17);
		pthread_mutex_destroy(&(*input)->monitor_timing);
		return ;
	}
	if (pthread_mutex_init(&(*input)->monitor, NULL) != 0)
	{
		write(2, "cannt init mutex\n", 17);
		pthread_mutex_destroy(&(*input)->monitor_timing);
		pthread_mutex_destroy(&(*input)->monitor);
		return ;
	}
	if (pthread_mutex_init(&(*input)->printing, NULL) != 0)
	{
		destroy_m(input);
		return ;
	}
	if (pthread_mutex_init(&(*input)->meals_moitor, NULL) != 0)
	{
		destroy_m(input);
		pthread_mutex_destroy(&(*input)->meals_moitor);
		return ;
	}
}

int	init_fork(int n, t_fork **fork)
{
	int	i;

	*fork = malloc(sizeof(t_fork) * n);
	if (!*fork)
		return (0);
	i = 0;
	while (i < n)
	{
		(*fork)[i].id = i + 1;
		if (pthread_mutex_init(&(*fork)[i].fork, NULL) != 0)
		{
			write(2, "cannt init mutex\n", 17);
			pthread_mutex_destroy(&(*fork)[i].fork);
			return (0);
		}
		i++;
	}
	return (1);
}

void	init_thread(t_philo **philo, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		if (pthread_create(&(*philo)[i].num_p, NULL, handel_thread,
			&(*philo)[i]) != 0)
		{
			write(2, "cann't creat thread\n", 20);
			return ;
		}
		i++;
	}
}

int	init_philo(t_philo **philo, int n, t_fork **fork, t_data *input)
{
	int	i;
	int	right;

	*(philo) = malloc(sizeof(t_philo) * n);
	if (!*philo)
		return (0);
	i = 0;
	while (i < n)
	{
		(*philo)[i].philo_id = i + 1;
		(*philo)[i].meals = 0;
		(*philo)[i].left = &(*fork)[i];
		(*philo)[i].data = input;
		(*philo)[i].stop = 0;
		protect_timing(&(*philo)[i]);
		if (i == n - 1)
			right = 0;
		else
			right = i + 1;
		(*philo)[i].right = &(*fork)[right];
		i++;
	}
	input->philo = *philo;
	return (1);
}
