/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:30:20 by yalee             #+#    #+#             */
/*   Updated: 2023/05/02 16:14:09 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	should_die(t_table *table)
{
	int	is_odd;

	is_odd = table->philo_num % 2;
	if (is_odd)
	{
		if (table->eat_time * 3 >= table->die_time || table->eat_time * 2
			+ table->sleep_time >= table->die_time)
			return (1);
	}
	else
	{
		if (table->eat_time * 2 >= table->die_time || table->eat_time
			+ table->sleep_time >= table->die_time)
			return (1);
	}
	return (0);
}

void	free_all(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->lock_thread_create);
	pthread_mutex_destroy(&table->lock_print);
	pthread_mutex_destroy(&table->lock_dead);
	pthread_mutex_destroy(&table->lock_checker);
	while (i < table->philo_num)
	{
		pthread_mutex_destroy(&table->philo[i].lock_eat);
		pthread_mutex_destroy(&table->forks[i]);
		i++;
	}
	free(table->philo);
}

long long	ft_atoi(const char *str)
{
	int			i;
	int			sgn;
	long long	res;

	i = 0;
	sgn = 1;
	res = 0;
	while (str[i] == ' ' || ((9 <= str[i]) && (str[i] <= 13)))
		i++;
	if (str[i] == '+')
		i++;
	else if (str[i] == '-')
	{
		sgn = -1;
		i++;
	}
	while (str[i] && ('0' <= str[i]) && (str[i] <= '9'))
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (sgn * res);
}

int	is_digits(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

long long	get_mili(void)
{
	struct timeval	te;
	long long		milliseconds;

	gettimeofday(&te, NULL);
	milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}
