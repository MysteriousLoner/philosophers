/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:18:09 by yalee             #+#    #+#             */
/*   Updated: 2023/05/01 23:33:02 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// void	check_data(t_table table)
// {
// 	int i;
	
// 	i = 0;
// 	printf("philo ded: %i\nphilo num: %i\nstart time: %lld\neat time: %lld\nsleep time: %lld\ndie time: %lld\ntime must eat: %i\n", table.philo_ded, table.philo_num, table.start_time, table.eat_time, table.sleep_time, table.die_time, table.time_must_eat);
// 	while(i < table.philo_num)
// 	{
// 		printf("philo name: %i\nis ded: %i\nisthinkin: %i\nis eatin: %i\nlast_eat: %lld\n", table.philo[i].name, table.philo[i].isded, table.philo[i].isthinking, table.philo[i].iseating, table.philo[i].time_last_eat);
// 		i++;
// 	}
// }

int	data_bad(t_table table)
{
	if (table.philo_num > 200 || table.philo_num < 1)
	{
		write(1, "Invalid philos!\n", 16);
		return (1);
	}
	if (table.die_time > 2147483647 || table.eat_time > 2147483647 || table.sleep_time > 2147483647 || table.time_must_eat > 2147483647)
	{
		write(1, "Invalid input!\n", 15);
		return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argv_bad(argv, argc))
	{
		write(2, "invalid input!\n", 14);
		return (0);
	}
	ini_data(argv, argc, &table);
	ini_forks(&table);
	if (data_bad(table))
		return (0);
	start_threads(&table);
	free_all(&table);
}