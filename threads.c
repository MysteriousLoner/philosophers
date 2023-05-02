/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:15 by yalee             #+#    #+#             */
/*   Updated: 2023/05/02 15:01:18 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	int	self;
	int	other;

	if (philo->name == philo->table->philo_num - 1)
		other = 0;
	else
		other = philo->name + 1;
	self = philo->name;
	pthread_mutex_lock(&philo->table->forks[self]);
	protected_printf(philo->name, 1, get_mili(), philo->table);
	pthread_mutex_lock(&philo->table->forks[other]);
	pthread_mutex_lock(&philo->lock_eat);
	philo->time_last_eat = get_mili();
	pthread_mutex_unlock(&philo->lock_eat);
	protected_printf(philo->name, 1, get_mili(), philo->table);
	protected_printf(philo->name, 2, get_mili(), philo->table);
	usleep(philo->table->eat_time * 1000);
	pthread_mutex_unlock(&philo->table->forks[self]);
	pthread_mutex_unlock(&philo->table->forks[other]);
	philo->isthinking = 1;
	pthread_mutex_lock(&philo->lock_eat);
	if (philo->table->time_must_eat > 0)
		philo->times_eaten++;
	pthread_mutex_unlock(&philo->lock_eat);
}

int	checker(t_philo *philo)
{
	long long	time;

	if (philo->times_eaten >= philo->table->time_must_eat && philo->table->time_must_eat > 0)
	{
		philo->dead = 1;
		return (0);
	}
	if (!philo->will_die)
		return(1);
	pthread_mutex_lock(&philo->lock_eat);
	time = get_mili() - philo->time_last_eat + 10;
	pthread_mutex_unlock(&philo->lock_eat);
	if (time > philo->fate)
	{
		usleep((philo->name % 2 * 1000) + (philo->name * 1000));
		pthread_mutex_lock(&philo->table->lock_checker);
		philo->table->philo_ded += 2;
		pthread_mutex_unlock(&philo->table->lock_checker);
		if (philo->dead == 0)
			protected_printf(philo->name, 5, time, philo->table);
		philo->dead = 1;
		return (0);
	}
	return (1);
}

void	*start_routine(void *args)
{
	long long	sleep;
	t_philo	*philo = (t_philo *)args;

	if (philo->table->philo_num == 1)
	{
		printf("[%lld] Philo number 0 died.\n", philo->table->die_time);
		return NULL;
	}
	while(!philo->dead)
	{
		if (philo->isthinking && !philo->dead)
			protected_printf(philo->name, 4, get_mili(), philo->table);
		if (checker(philo) && !philo->dead)
			philo_eat(philo);
		if (checker(philo) && !philo->dead)
		{
			sleep = get_mili() + philo->table->sleep_time;
			protected_printf(philo->name, 3, get_mili(), philo->table);
			while (get_mili() < sleep)
				usleep(10);
		}
	}
	return NULL;
}

void	start_threads(void *args)
{
	int	i;
	i = 0;
	t_table *table = (t_table *)args;

	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->lock_thread_create);
		pthread_mutex_lock(&table->philo[i].lock_eat);
		table->philo[i].time_last_eat = get_mili();
		pthread_mutex_unlock(&table->philo[i].lock_eat);
		pthread_create(&table->philo[i].life, NULL, start_routine, &table->philo[i]);
		i += 2;
		pthread_mutex_unlock(&table->lock_thread_create);
	}
	i = 1;
	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->lock_thread_create);
		pthread_mutex_lock(&table->philo[i].lock_eat);
		table->philo[i].time_last_eat = get_mili();
		pthread_mutex_unlock(&table->philo[i].lock_eat);
		pthread_create(&table->philo[i].life, NULL, start_routine, &table->philo[i]);
		i += 2;
		pthread_mutex_unlock(&table->lock_thread_create);
	}
	join_threads(table);
}

void	join_threads(void *args)
{
	int i;
	
	i = 0;
	t_table *table = (t_table *)args;
	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->lock_thread_create);
		pthread_join(table->philo[i].life, NULL);
		i++;
		pthread_mutex_unlock(&table->lock_thread_create);
	}
}