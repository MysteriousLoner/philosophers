/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:31:43 by yalee             #+#    #+#             */
/*   Updated: 2023/04/21 17:11:45 by yalee            ###   ########.fr       */
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
		i++;
	}
}

int ini_data(char **argv, int argc, t_table *table)
{
	if (ft_atoi(argv[1]) > 200 || ft_atoi(argv[1]) <= 0)
	{
		write(2, "Overpopulation!\n", 16);
		return (0);
	}
	table->philo_num = ft_atoi(argv[1]);
	table->philo = (t_philo *)malloc(sizeof(t_philo) * ft_atoi(argv[1]));
	table->forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * ft_atoi(argv[1]));
	table->die_time = ft_atoi(argv[2]);
	table->eat_time = ft_atoi(argv[3]);
	table->sleep_time = ft_atoi(argv[4]);
	if (argc == 6)
		table->time_must_eat = ft_atoi(argv[5]);
	else
		table->time_must_eat = 0;
	if (table->die_time < 0 || table->eat_time < 0 || table->sleep_time < 0 ||
		table->time_must_eat < 0 || table->die_time > 2147483647 || table->eat_time > 2147483647 ||
		table->sleep_time > 2147483647 || table->time_must_eat > 2147483647)
		return (0);
	else
	{
		table->start_time = get_mili();
		give_birth(table);
		return (1);
	}
}

void	ini_forks(t_table *table, char **argv)
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