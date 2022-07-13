/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:48:00 by jting             #+#    #+#             */
/*   Updated: 2022/07/13 13:15:43 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
// while they haven't all eaten it loops through all the threads checking that
// none of the philos have exceeded their time to eat.
// then checks if still alive and will break out of the loop.
// proceeds to check if all the philos have eaten the required amount for the 
// process to stop if it does it will also break out the loop.
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
			usleep(50);
		}
		if (!(r->is_alive))
			break ;
		i = 1;
		while (r->times_eaten != -1 && i < r->philo_num
			&& p[i].x_eaten >= r->times_eaten)
			i++;
		if (i == r->philo_num)
			r->all_eaten = 1;
	}
}

// Prints grabbing the fork and sleeps for time to die
int	solo_phil(t_rules *r)
{
	printf("0ms	1 grabs a fork\n");
	usleep(r->time_to_die * 1000);
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
