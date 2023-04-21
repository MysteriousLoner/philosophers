/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:18:36 by yalee             #+#    #+#             */
/*   Updated: 2023/04/21 17:11:00 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <sys/time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

typedef	struct s_philo
{
	int			name;
	int			isded;
	long long 	time_last_eat;
	pthread_t	life;
	t_table		*table;
}		t_philo;

typedef struct s_table
{
	pthread_mutex_t *forks;
	t_philo			*philo;
	int				philo_ded;
	int				philo_num;
	long long		start_time;
	long long		eat_time;
	long long		sleep_time;
	long long		die_time;
	int				time_must_eat;
}		t_table;

int ini_data(char **argv, int argc, t_table *table);
int argv_bad(char **argv, int argc);
long long ft_atoi(const char *str);
int is_digits(char **argv);
long long get_mili();
#endif