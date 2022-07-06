/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:35:41 by jting             #+#    #+#             */
/*   Updated: 2022/07/06 15:20:39 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_init(t_rules *data)
{
	int		i;
	t_philo	*phi;

	phi = data->philos;
	i = data->philo_num;
	while (--i >= 0)
	{
		data->philos[i].id = i;
		data->philos[i].left_fork = i;
		data->philos[i].right_fork = (i + 1) % i;
		data->philos[i].rules = data;
		data->philos[i].eat_time = 0;
	}
	return (1);
}

int	init_mutex(t_rules *r)
{
	int	i;

	i = r->philo_num;
	while (--i >= 0)
	{
		if (pthread_mutex_init(&(r->forks[i]), NULL))
			return (1);
	}
	if (pthread_mutex_init(&(r->eaten_meal), NULL))
		return (1);
	if (pthread_mutex_init(&(r->writing), NULL))
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
		data->times_eaten = phil_atoi(5);
	else
		data->times_eaten = -1;
	if (!phil_init(data))
		return (0);
	if (!init_mutex(data))
		return (0);
	return (1);
}
