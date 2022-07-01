/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:57:16 by jting             #+#    #+#             */
/*   Updated: 2022/07/01 10:51:38 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void	eat(t_philo	*phils, int phil)
{
	t_rules	*rule;

	rule = phils->rules;
	pthread_mutex_lock(&rule->forks[phils->left_fork]);
	pthread_mutex_lock(&rule->forks[phils->right_fork]);
	printf("%lims	%i has taken a fork\n", get_time(), phils->id);
	printf("%lims	%i has taken a fork\n", get_time(), phils->id);
	printf("%lims	%i is eating\n", phil);
	phils->eat_time = get_time();
	usleep(phils->eat_time * 1000);
	pthread_mutex_unlock(&rule->forks[phils->left_fork]);
	pthread_mutex_unlock(&rule->forks[phils->right_fork]);
	printf("%lims	%i is thinking\n", get_time(), phils->id);
	(phils->each_eat)++;
}

/* For each philosopher that is initiated it will need to initially check
// if there are any forks available. If there is it will take the fork and 
 eat for x ms while muting the data. 
*/
void	*looping(t_rules	*data)
{
	t_rules		*rules;
	t_philo		*phils;

	if (philos->id % 2)
		usleep(10000);
	while (data->is_alive)
	{
		eat(data, data->philo_num);
		if (data->all_eaten)
			break ;
		printf("%lims	%i is sleeping\n", get_time(), phils->id);
	}	
}