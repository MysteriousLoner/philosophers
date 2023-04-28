/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:31:43 by yalee             #+#    #+#             */
/*   Updated: 2023/04/28 19:16:19 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	give_birth(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		table->philo[i].name = i;
		table->philo[i].isded = 0;
		table->philo[i].time_last_eat = 0;
		table->philo[i].table = table;
		table->philo[i].isthinking = 0;
		table->philo[i].times_eaten = 0;
		i++;
	}
}

void	ini_data(char **argv, int argc, t_table *table)
{
	table->philo_num = ft_atoi(argv[1]);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	table->die_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	table->philo_ded = -1;
	pthread_mutex_init(&table->lock_thread_create, NULL);
	pthread_mutex_init(&table->lock_print, NULL);
	pthread_mutex_init(&table->lock_god, NULL);
	pthread_mutex_init(&table->lock_subgod, NULL);
	pthread_mutex_init(&table->spawn_god, NULL);
	if (argc == 6)
		table->time_must_eat = ft_atoi(argv[5]);
	else
		table->time_must_eat = -1;
	table->start_time = get_mili();
	give_birth(table);
}

void	ini_forks(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_mutex_init(&(table->forks[i]), NULL);
		i++;
	}
}

int argv_bad(char **argv, int argc)
{
	if (argc > 6 || argc < 5)
		return (1);
	if (is_digits(argv))
		return (1);
	return (0);
}