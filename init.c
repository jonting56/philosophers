/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:35:41 by jting             #+#    #+#             */
/*   Updated: 2022/06/29 17:00:03 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_init(t_rules *data)
{
	int	i;

	i = data->philo_num;
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % i;
		data->philos[i].rules = data;
		data->philos[i].eat_time = 0;
		pthread_mutex_init(&(data->forks[i]), NULL);
	}
	return (1);
}


int	init_struct(t_rules *data, int ac, char **av)
{
	int	i;

	i = -1;
	if ((ac < 5 || ac > 6) || !isnum(ac, av))
		return (0);
	data = malloc(sizeof(t_rules));
	data->philo_num = phil_atoi(1);
	data->time_to_die = phil_atoi(2);
	data->time_to_eat = phil_atoi(3);
	data->time_to_sleep = phil_atoi(4);
	data->is_alive = 1;
	data->all_eaten = 0;
	if (ac == 5)
		data->time_to_eat = phil_atoi(5);
	else
		data->time_to_eat = -1;
	if (!phil_init(data))
		return (0);
	return (1);
}
