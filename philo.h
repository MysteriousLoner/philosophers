/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:18:36 by yalee             #+#    #+#             */
/*   Updated: 2023/05/01 22:19:30 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define MAX_INT = 2147483647;

typedef struct s_philo t_philo;
typedef struct s_table t_table;

typedef struct s_table
{
	pthread_mutex_t *forks;
	pthread_mutex_t lock_thread_create;
	pthread_mutex_t	lock_print;
	pthread_mutex_t lock_checker;
	pthread_t		checker;
	t_philo			*philo;
	int				philo_ded;
	int				philo_num;
	long long		start_time;
	long long		eat_time;
	long long		sleep_time;
	long long		die_time;
	int				time_must_eat;
}		t_table;

typedef struct s_philo
{
	int name;
	int isthinking;
	int	times_eaten;
	long long time_last_eat;
	pthread_t life;
	t_table *table;
	pthread_mutex_t lock_eat;
} 		t_philo;

typedef	struct	s_print_args
{
	int	name;
	int	action;
	long long	time;
}		t_print_args;

void free_all(t_table *table);
void protected_printf(int name, int action, long long time, t_table *table);
int lock_fork(t_philo *philo);
void try_take_fork(t_philo *philo);
void *start_routine(void *args);
void start_threads(void *args);
void check_data(t_table table);
int data_bad(t_table table);
long long ft_atoi(const char *str);
int is_digits(char **argv);
long long get_mili();
void give_birth(t_table *table);
void ini_data(char **argv, int argc, t_table *table);
void ini_forks(t_table *table);
int argv_bad(char **argv, int argc);
#endif