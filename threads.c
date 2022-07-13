/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:57:16 by jting             #+#    #+#             */
/*   Updated: 2022/07/13 13:04:20 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// Iterates through all threads and joins them
// Continues to iterate through fork mutexs
void	thread_exit(t_rules *r, t_philo *phil)
{
	int	i;

	i = 0;
	while (++i <= r->philo_num)
		pthread_join(phil[i].thread_id, NULL);
	i = 0;
	while (++i <= r->philo_num)
		pthread_mutex_destroy(&(r->forks[i]));
	pthread_mutex_destroy(&(r->writing));
}

// Function to allow philos to eat, mutes forks before eating
// while printing the associated action, reassigns the time variable
// for each philo to reset their last time eaten, also adds to counter
// to to check amount of times eaten if required, unmutes forks after finishing
void	eat(t_philo	*phils)
{
	t_rules	*rule;

	rule = phils->rules;
	pthread_mutex_lock(&rule->forks[phils->left_fork]);
	action_dis(rule, phils->id, "has taken a fork");
	pthread_mutex_lock(&rule->forks[phils->right_fork]);
	action_dis(rule, phils->id, "has taken a fork");
	pthread_mutex_lock(&(rule->eaten_meal));
	action_dis(rule, phils->id, "is eating");
	phils->eat_time = get_time();
	pthread_mutex_unlock(&(rule->eaten_meal));
	phi_sleep(rule->time_to_eat, rule);
	(phils->x_eaten)++;
	pthread_mutex_unlock(&rule->forks[phils->left_fork]);
	pthread_mutex_unlock(&rule->forks[phils->right_fork]);
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
	while (r->is_alive)
	{	
		eat(phils);
		if (r->all_eaten)
			break ;
		action_dis(r, phils->id, "is sleeping");
		phi_sleep(r->time_to_sleep, r);
		action_dis(r, phils->id, "is thinking");
	}
	return (NULL);
}

// Iterates through all the philos creating threads 
// for each one running the threads
// function which has all the required checks to allow for them to eat.
// After that runs the death checker and frees 
// the threads after either all philos
// have eaten or the time of death is reached before eating.
int	feastin(t_rules	*r)
{
	int		i;
	t_philo	*phil;

	i = 0;
	phil = r->philos;
	r->first_time = get_time();
	while (++i <= r->philo_num)
	{
		pthread_create(&(phil[i].thread_id), NULL, threads, &(phil[i]));
		phil[i].eat_time = get_time();
	}
	death_check(r, r->philos);
	thread_exit(r, phil);
	return (0);
}

// Mutes the writing to stop other threads from printing to the console,
// prints the required actions.
void	action_dis(t_rules *r, int id, char *s)
{
	pthread_mutex_lock(&(r->writing));
	if (r->is_alive)
	{
		printf("%llims	", get_time() - r->first_time);
		printf("%i ", id);
		printf("%s\n", s);
	}
	pthread_mutex_unlock(&(r->writing));
}
