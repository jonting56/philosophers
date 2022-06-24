/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:57:16 by jting             #+#    #+#             */
/*   Updated: 2022/06/24 17:24:37 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	eat(t_thread *data, int	phil)
{
	long	time_since_eat;

	pthread_mutex_lock(&data->philos[phil]);
	pthread_mutex_lock(&data->philos[phil + 1]);
}

// For each philosopher that is initiated it will need to initially check
// if there are any forks available. If there is it will take the fork and 
// eat for x ms while muting the data. 

void	*looping(t_thread *data)
{
	int	num;

	num = (data->philo_num);
	while (data->is_alive && data->times_eaten != 0)
	{
		while (data->is_alive)
		{
			//if (data->time_to_die < get_time())
				//philo_died();

		}
		eat(data, data->philo_num);
	}	
}
