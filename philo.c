/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:48:00 by jting             #+#    #+#             */
/*   Updated: 2022/07/08 16:30:26 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	death_check(t_rules *r, t_philo *p)
{
	int	i;

	while (!(r->all_eaten))
	{
		i = 0;
		while (++i <= r->philo_num && r->is_alive)
		{
			pthread_mutex_lock(&(r->eaten_meal));
			if (time_diff(get_time(), p[i].eat_time) >= r->time_to_die)
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
			&& p[i].x_eaten >= r->times_eaten)
			i++;
		if (i == r->philo_num)
			r->all_eaten = 1;
	}
}

int	solo_phil(t_rules *r)
{
	printf("0ms	1 grabs a fork\n");
	printf("%lims 	1 has died\n", r->time_to_die);
	return (-1);
}

int	main(int ac, char **av)
{
	t_rules		rules;

	if (!init_struct(&rules, ac, av))
		return (printf("Please enter correct variables\n"));
	if (rules.philo_num == 1)
		return (solo_phil(&rules));
	if (!feastin(&rules))
		return (0);
}
