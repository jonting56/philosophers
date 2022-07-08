/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:35:41 by jting             #+#    #+#             */
/*   Updated: 2022/07/08 16:16:13 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_init(t_rules *rules)
{
	int		i;

	i = rules->philo_num + 1;
	while (--i > 0)
	{
		rules->philos[i].id = i;
		rules->philos[i].left_fork = i;
		rules->philos[i].right_fork = (i + 1) % rules->philo_num;
		rules->philos[i].rules = rules;
		rules->philos[i].x_eaten = 0;
		rules->philos[i].eat_time = 0;
	}
	return (1);
}

int	init_mutex(t_rules *r)
{
	int	i;

	i = r->philo_num + 1;
	while (--i > 0)
	{
		printf("%d mutes made\n", i);
		if (pthread_mutex_init(&(r->forks[i]), NULL))
			return (0);
	}
	if (pthread_mutex_init(&(r->eaten_meal), NULL))
		return (0);
	if (pthread_mutex_init(&(r->writing), NULL))
		return (0);
	return (1);
}

int	init_struct(t_rules *rules, int ac, char **av)
{
	if ((ac < 5 || ac > 6) || !isnum(av))
		return (0);
	rules->philo_num = phil_atoi(av[1]);
	rules->time_to_die = phil_atoi(av[2]);
	rules->time_to_eat = phil_atoi(av[3]);
	rules->time_to_sleep = phil_atoi(av[4]);
	rules->is_alive = 1;
	rules->all_eaten = 0;
	if (ac == 6)
		rules->times_eaten = phil_atoi(av[5]);
	else
		rules->times_eaten = -1;
	if (!init_mutex(rules))
		return (0);
	if (!phil_init(rules))
		return (0);
	return (1);
}
