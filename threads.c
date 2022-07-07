/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:57:16 by jting             #+#    #+#             */
/*   Updated: 2022/07/07 16:20:18 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	thread_exit(t_rules *r, t_philo *phil)
{
	int	i;

	i = 0;
	while (i < r->philo_num)
	{
		pthread_join(phil[i].thread_id, NULL);
		i++;
	}
	i = 0;
	while (i < r->philo_num)
	{
		pthread_mutex_destroy(&(r->forks[i]));
		i++;
	}
	pthread_mutex_destroy(&(r->writing));
}

void	eat(t_philo	*phils)
{
	t_rules	*rule;

	rule = phils->rules;
	pthread_mutex_lock(&rule->forks[phils->left_fork]);
	pthread_mutex_lock(&rule->forks[phils->right_fork]);
	printf("%llims	%i has taken a fork\n",
		time_diff(phils->eat_time, get_time()), phils->id);
	printf("%llims	%i has taken a fork\n",
		time_diff(phils->eat_time, get_time()), phils->id);
	pthread_mutex_lock(&(rule->eaten_meal));
	printf("%llims	%i is eating\n",
		time_diff(phils->eat_time, get_time()), phils->id);
	phils->eat_time = get_time();
	pthread_mutex_unlock(&(rule->eaten_meal));
	phi_sleep(rule->time_to_eat, get_time());
	pthread_mutex_unlock(&rule->forks[phils->left_fork]);
	pthread_mutex_unlock(&rule->forks[phils->right_fork]);
	printf("%llims	%i is thinking\n", get_time(), phils->id);
	(phils->each_eat)++;
}

/* For each philosopher that is initiated it will need to initially check
// if there are any forks available. If there is it will take the fork and 
 eat for x ms while muting the rules. 
*/
void	*threads(void	*ph)
{
	t_rules		*r;
	t_philo		*phils;

	phils = (t_philo *)ph;
	r = phils->rules;
	if (phils->id % 2)
		usleep(15000);
	printf("%d pre-eat\n", phils->id);
	while (r->is_alive)
	{	
		eat(phils);
		if (r->all_eaten)
			break ;
		action_dis(r, phils->id, "is sleeping\n");
		phi_sleep(phils->eat_time, r);
		action_dis(r, phils->id, "is thinking\n");
	}
	return (NULL);
}

int	feastin(t_rules	*r)
{
	int		i;
	t_philo	*phil;

	i = 1;
	phil = r->philos;
	r->first_time = get_time();
	while (i <= r->philo_num)
	{
		pthread_create(&(phil[i].thread_id), NULL, threads, &(phil[i]));
		phil[i].eat_time = get_time();
		i++;
	}
	death_check(r, r->philos);
	thread_exit(r, phil);
	return (0);
}

void	action_dis(t_rules *r, int id, char *s)
{
	pthread_mutex_lock(&(r->writing));
	if (!(r->is_alive))
	{
		printf("%lli ", get_time() - r->first_time);
		printf("%i ", id);
		printf("%s\n", s);
	}
	pthread_mutex_unlock(&(r->writing));
}
