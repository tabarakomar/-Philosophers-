/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabarak <tabarak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 16:29:20 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/27 22:58:35 by tabarak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	destroy_m(t_data **input)
{
	write(2, "cannt init mutex\n", 17);
	pthread_mutex_destroy(&(*input)->monitor_timing);
	pthread_mutex_destroy(&(*input)->monitor);
	pthread_mutex_destroy(&(*input)->printing);
}

long	ft_atoi(const char *str)
{
	int		i;
	long	a;
	int		sign;

	sign = 1;
	i = 0;
	a = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = sign * -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		a = a * 10 + (str[i] - '0');
		i++;
	}
	return (a * sign);
}

long	anatoi(const char *str)
{
	long	s;

	s = ft_atoi(str);
	if (s > INT_MAX || s < INT_MIN)
		return (0);
	return (1);
}

long	time_right_now(void)
{
	struct timeval	tv;
	long			time_s;
	long			time_lefts;
	long			total_time;

	if ((gettimeofday(&tv, NULL)) != 0)
	{
		return (0);
	}
	time_s = tv.tv_sec * 1000;
	time_lefts = tv.tv_usec / 1000;
	total_time = time_s + time_lefts;
	return (total_time);
}

void	sleeping(long s_time)
{
	usleep(s_time * 1000);
}
