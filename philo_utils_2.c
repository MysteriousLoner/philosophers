/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/02 16:14:28 by yalee             #+#    #+#             */
/*   Updated: 2023/05/02 16:16:34 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long long	cheese(long long time)
{
	int			i;
	int			temp;
	long long	ori;
	long long	time2;

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
	if (ori > (temp * 10 * 10 / 2) + temp * 10)
		ori -= 8;
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
		return ;
	}
	pthread_mutex_lock(&table->lock_dead);
	if (action == 5 && table->philo_ded == 1)
		printf("[%lld] phino number %i died\n", time / 10 * 10, name);
	table->philo_ded = 2;
	pthread_mutex_unlock(&table->lock_dead);
	pthread_mutex_unlock(&table->lock_checker);
	pthread_mutex_unlock(&table->lock_print);
}
