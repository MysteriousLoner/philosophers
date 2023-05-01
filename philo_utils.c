/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 13:30:20 by yalee             #+#    #+#             */
/*   Updated: 2023/05/02 02:55:45 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

void	protected_printf(int name, int action, long long time, t_table *table)
{
	pthread_mutex_lock(&table->lock_print);
	pthread_mutex_lock(&table->lock_checker);
	if (table->philo_ded < 0)
	{
		pthread_mutex_unlock(&table->lock_checker);
		printf("[%lld]", ((time - table->start_time) / 10 * 10));
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