/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:48:00 by jting             #+#    #+#             */
/*   Updated: 2022/07/06 15:45:27 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_check(t_rules *r, t_philo *p)
{
	int	i;

	while (!(r->all_eaten))
	{
		i = -1;
		while (++i < r->philo_num && r->is_alive)
		{
			pthread_mutex_lock(&(r->eaten_meal));
			if (time_diff(p[i].eat_time, get_time()) > r->time_to_die)
			{
				action_dis(r, i, "died\n");
				r->is_alive = 0;
			}
			pthread_mutex_unlock(&(r->eaten_meal));
			usleep(100);
		}
		if (!(r->is_alive))
			break ;
		i = 0;
		while (r->times_eaten != -1 && i < r->philo_num
			&& p[i].each_eat >= r->times_eaten)
			i++;
		if (i == r->philo_num)
			r->all_eaten = 1;
	}
}

int	main(int ac, char **av)
{
	t_rules		*data;
	int			i;

	i = 0;
	if (!init_struct(data, ac, av))
		return (0);
	if (!feastin(data))
		return (0);
}
