/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/29 14:35:41 by jting             #+#    #+#             */
/*   Updated: 2022/07/07 15:41:01 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_init(t_rules *rules)
{
	int		i;
	t_philo	*phi;

	phi = rules->philos;
	i = 1;
	while (i <= rules->philo_num)
	{
		rules->philos[i].id = i;
		rules->philos[i].left_fork = i;
		rules->philos[i].right_fork = (i + 1) % i;
		rules->philos[i].rules = rules;
		rules->philos[i].eat_time = 0;
		i++;
	}
	return (1);
}

int	init_mutex(t_rules *r)
{
	int	i;

	i = 1;
	while (i <= r->philo_num)
	{
		if (pthread_mutex_init(&(r->forks[i]), NULL))
			return (0);
		i++;
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
	if (!phil_init(rules))
		return (0);
	if (!init_mutex(rules))
		return (0);
	return (1);
}
