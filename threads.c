/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:57:16 by jting             #+#    #+#             */
/*   Updated: 2022/07/06 15:58:21 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	exit(t_rules *r, t_philo *phil)
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

void	eat(t_philo	*phils, int phil)
{
	t_rules	*rule;

	rule = phils->rules;
	pthread_mutex_lock(&rule->forks[phils->left_fork]);
	pthread_mutex_lock(&rule->forks[phils->right_fork]);
	printf("%llims	%i has taken a fork\n", get_time(), phils->id);
	printf("%llims	%i has taken a fork\n", get_time(), phils->id);
	printf("%llims	%i is eating\n", phil);
	phils->eat_time = get_time();
	usleep(phils->eat_time * 1000);
	pthread_mutex_unlock(&rule->forks[phils->left_fork]);
	pthread_mutex_unlock(&rule->forks[phils->right_fork]);
	printf("%llims	%i is thinking\n", get_time(), phils->id);
	(phils->each_eat)++;
}

/* For each philosopher that is initiated it will need to initially check
// if there are any forks available. If there is it will take the fork and 
 eat for x ms while muting the data. 
*/
void	*threads(void	*ph)
{
	t_rules		*r;
	t_philo		*phils;

	phils = (t_philo *)ph;
	r = phils->rules;
	if (phils->id % 2)
		usleep(10000);
	while (r->is_alive)
	{
		eat(r, r->philo_num);
		if (r->all_eaten)
			break ;
		action_dis(r, phils->id, "is sleeping\n");
		phi_sleep(r, phils->id);
		action_dis(r, phils->id, "is thinking\n");
	}
	return ;
}

int	feastin(t_rules	*r)
{
	int		i;
	t_philo	*phil;

	i = 0;
	phil = r->philos;
	r->first_time = get_time();
	while (i < r->philo_num)
	{
		pthread_create(&(phil[i].thread_id), NULL, threads, &(phil[i]));
		phil[i].eat_time = get_time();
		i++;
	}
	death_check(r, r->philos);
	exit(r, phil);
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