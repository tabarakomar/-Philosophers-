/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabarak <tabarak@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/09 15:08:58 by talshoub          #+#    #+#             */
/*   Updated: 2026/02/27 23:33:35 by tabarak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct s_data	t_data;
typedef struct s_fork	t_fork;
typedef struct s_philo	t_philo;
typedef struct s_times
{
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
}						t_time;

typedef struct s_data
{
	long				number_of_philo;
	long				number_of_fork;
	long				number_must_eat;
	long				start_eating;
	int					is_someone_died;
	t_time				*time;
	t_fork				*fork;
	t_philo				*philo;
	pthread_mutex_t		monitor;
	pthread_mutex_t		monitor_num_of_meals;
	pthread_mutex_t		monitor_timing;
	pthread_mutex_t		printing;
	pthread_mutex_t		meals_moitor;
}						t_data;

typedef struct s_fork
{
	pthread_mutex_t		fork;
	int					id;
}						t_fork;

typedef struct s_philo
{
	int					philo_id;
	int					meals;
	long				time_start_eating;
	int					stop;
	t_fork				*left;
	t_fork				*right;
	pthread_t			num_p;
	t_data				*data;
}						t_philo;

int						checking_argument(char **argv);
int						check_if_num(char *argv);
long					ft_atoi(const char *str);
long					anatoi(const char *str);
long					time_right_now(void);
void					start(t_data **input, char **argv);
int						init_fork(int n, t_fork **fork);
void					is_sleeping(t_philo *philo);
void					is_eating(t_philo *philo);
void					is_thinking(t_philo *philo);
void					*handel_thread(void *arg);
void					init_thread(t_philo **philo, int n);
void					init_thread_joing(t_philo *philo, int n);
int						init_philo(t_philo **philo, int n, t_fork **fork,
							t_data *input);
int						checking_death(long time_to_die, long time_now,
							long time_of_last_meal);
void					is_death(t_data *input, int n);
int						checking_num_of_meals(t_philo *philo);
int						philo_odd(t_philo *philo);
int						philo_even(t_philo *philo);
void					protect_timing(t_philo *philo);
void					simulation(t_data *input);
int						initilize(t_data **input, char **argv, t_fork **fork,
							t_philo **philo);
void					protect_printing(t_philo *philo, char *str);
int						meals_done(t_data *input);
int						first_step(int argc, char **argv);
void					init_mutex(t_data **input);
void					destroy_m(t_data **input);
int						nor_check(t_philo *philo);
int						meals_done_norm(t_data *input);
void					protect_timing_norm(t_philo *philo, long *time_now,
							long *time_of_last_meal);
void					protect_print_death(t_data *input, int i);
void					locking_death(t_data *input);
void					memset_fun_norm(t_time **times, t_data **input);
void					free_things(t_data **input, t_time **times);
void					sleeping(long s_time);
void					philo_odd_waitiig(t_philo *philo);
void					philo_even_wating(t_philo *philo);
#endif
