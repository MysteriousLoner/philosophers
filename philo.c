/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yalee <yalee@student.42.fr.com>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/18 17:18:09 by yalee             #+#    #+#             */
/*   Updated: 2023/04/21 17:48:25 by yalee            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->philo_num)
	{
		pthread_create(table->philo[i].life, NULL, )
	}
}

int	main(int argc, char **argv)
{
	t_table	table;
	
	if (argv_bad(argv, argc))
	{
		write(2, "invalid input!\n", 14);
		return (0);
	}
	if (!ini_data(argv, argc, &table))
		return (0);
	ini_forks(&table);
	start_threads(table);
}