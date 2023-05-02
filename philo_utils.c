/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:30:20 by yalee             #+#    #+#             */
/*   Updated: 2023/05/02 15:30:11 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int should_die(t_table *table)
{
	int is_odd;

	is_odd = table->philo_num % 2;
	if (is_odd)
	{
		if (table->eat_time * 3 >= table->die_time || table->eat_time * 2 + table->sleep_time >= table->die_time)
			return (1);
	}
	else
	{
		if (table->eat_time * 2 >= table->die_time || table->eat_time + table->sleep_time >= table->die_time)
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

long long ft_atoi(const char *str)
{
	int i;
	int sgn;
	long long res;

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

int is_digits(char **argv)
{
	int i;
	int j;

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

long long	get_mili()
{
	struct timeval te;
	gettimeofday(&te, NULL);
	long long milliseconds = te.tv_sec * 1000LL + te.tv_usec / 1000;
	return (milliseconds);
}

long long	cheese(long long time)
{
	int	i;
	int temp;
	long long	ori;
	long long	time2;

	// printf("time: %lld\n", time);
	if (time <= 10)
		return (0);
	i = 0;
	ori = time;
	time2 = time;
	temp = 1;
	while (time2 >= 10)
	{
		time2 = time2 / 10;
		i = i + 1;
	}
	while (i - 1 > 0)
	{
		temp *= 10;
		i--;
	}
	// if (ori > (temp * 10 * 10 / 2) + temp * 10)
	// 	ori -= 8;
	return ((ori / temp) * temp);
}

void	protected_printf(int name, int action, long long time, t_table *table)
{
	pthread_mutex_lock(&table->lock_print);
	pthread_mutex_lock(&table->lock_checker);
	if (table->philo_ded < 0)
	{
		pthread_mutex_unlock(&table->lock_checker);
		time = cheese(time - table->start_time);
		printf("[%lld]", time);
		if (action == 1)
			printf(" Philo number %i grabbed a fork.\n", name);
		if (action == 2)
			printf(" Philo number %i is eatin.\n", name);
		if (action == 3)
			printf(" Philo number %i is sleeping.\n", name);
		if (action == 4)
			printf(" Philo number %i is thinking.\n", name);
		pthread_mutex_unlock(&table->lock_print);
		return;
	}
	pthread_mutex_lock(&table->lock_dead);
	if (action == 5 && table->philo_ded == 1)
		printf("[%lld] phino number %i died\n", time / 10 * 10, name);
	table->philo_ded = 2;
	pthread_mutex_unlock(&table->lock_dead);
	pthread_mutex_unlock(&table->lock_checker);
	pthread_mutex_unlock(&table->lock_print);
}