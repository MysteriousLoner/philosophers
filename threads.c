/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/27 11:05:15 by yalee             #+#    #+#             */
/*   Updated: 2023/04/28 19:34:50 by yalee            ###   ########.fr       */
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
	philo->time_last_eat = get_mili();
	protected_printf(philo->name, 1, get_mili(), philo->table);
	protected_printf(philo->name, 2, get_mili(), philo->table);
	usleep(philo->table->eat_time * 1000);
	pthread_mutex_unlock(&philo->table->forks[self]);
	pthread_mutex_unlock(&philo->table->forks[other]);
	philo->isthinking = 1;
	if (philo->table->time_must_eat > 0)
		philo->times_eaten++;
}

void	*physics(void *args)
{
	t_philo *philo = (t_philo *)args;

	// (void)philo;
	pthread_mutex_lock(&philo->table->lock_god);
	while (philo->table->philo_ded < 0)
	{
		if (get_mili() - philo->time_last_eat > philo->table->die_time && philo->table->philo_ded < 0)
		{
			pthread_mutex_lock(&philo->table->lock_subgod);
			philo->table->philo_ded = philo->name;
			// pthread_mutex_lock(&philo->table->lock_subgod);
			printf("[%lld] Philo number %i died.\n", (get_mili() - philo->table->start_time - 1), philo->table->philo_ded);
			pthread_mutex_unlock(&philo->table->forks[philo->name]);
			pthread_mutex_unlock(&philo->table->lock_subgod);
		}
	}
	pthread_mutex_unlock(&philo->table->lock_god);
	pthread_detach(philo->god);
	return NULL;
}

int	all_not_fed(t_table *table)
{
	int	i;
	
	i = 0;
	// pthread_mutex_lock(&table->lock_subgod);
	if (table->time_must_eat < 0)
		return (1);
	while (i < table->philo_num)
	{
		if (table->philo[i].times_eaten < table->time_must_eat)
			return (1);
		i++;
	}
	// pthread_mutex_lock(&table->lock_subgod);
	return (0);
}

void	*start_routine(void *args)
{
	t_philo	*philo = (t_philo *)args;

	while(philo->table->philo_ded < 0 && all_not_fed(philo->table))
	{
		if (philo->isthinking && philo->table->philo_ded < 0 && all_not_fed(philo->table))
			protected_printf(philo->name, 4, get_mili(), philo->table);
		if (philo->table->philo_ded < 0 && all_not_fed(philo->table))
			philo_eat(philo);
		// printf("eaten\n");
		if (philo->table->philo_ded < 0 && all_not_fed(philo->table))
		{
			protected_printf(philo->name, 3, get_mili(), philo->table);
			usleep(philo->table->sleep_time * 1000);
		}
	}
	// printf("returned\n");
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
		table->philo[i].time_last_eat = get_mili();
		pthread_create(&table->philo[i].life, NULL, start_routine, &table->philo[i]);
		pthread_create(&table->philo[i].god, NULL, physics, &table->philo[i]);
		i += 2;
		pthread_mutex_unlock(&table->lock_thread_create);
	}
	i = 1;
	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->lock_thread_create);
		table->philo[i].time_last_eat = get_mili();
		pthread_create(&table->philo[i].life, NULL, start_routine, &table->philo[i]);
		pthread_create(&table->philo[i].god, NULL, physics, &table->philo[i]);
		i += 2;
		pthread_mutex_unlock(&table->lock_thread_create);
	}
	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_lock(&table->lock_thread_create);
		pthread_join(table->philo[i].life, NULL);
		i++;
		pthread_mutex_unlock(&table->lock_thread_create);
	}
}