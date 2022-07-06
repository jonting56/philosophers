/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:42:55 by jting             #+#    #+#             */
/*   Updated: 2022/07/06 15:58:20 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <string.h>
# include <pthread.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>

typedef struct s_rules
{
	int				philo_num;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	int				all_eaten;	
	int				is_alive;
	long			first_time;
	int				times_eaten;
	t_philo			philos[250];
	pthread_mutex_t	forks[250];
	pthread_mutex_t	writing;
	pthread_mutex_t	eaten_meal;
}	t_rules;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				each_eat;
	long			eat_time;
	pthread_t		thread_id;
	int				id;
	t_rules			*rules;
}	t_philo;

int			init_struct(t_rules *data, int ac, char **av);
long long	time_diff(long long prev, long long cur);
long long	get_time(void);
void		phi_sleep(long long time, t_rules *r);
void		*threads(t_rules data);
int			feastin(t_rules *r);
void		eat(t_rules *data, int phil);
void		action_dis(t_rules *r, int id, char *s);
void		exit(t_rules *r, t_philo *phil);
int			phil_init(t_rules *data);
int			init_mutex(t_rules *r);
#endif