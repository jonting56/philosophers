/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:42:55 by jting             #+#    #+#             */
/*   Updated: 2022/07/08 15:37:39 by jting            ###   ########.fr       */
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

struct	s_rules;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				x_eaten;
	long			eat_time;
	pthread_t		thread_id;
	int				id;
	struct s_rules	*rules;
}	t_philo;

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
	t_philo			philos[200];
	pthread_mutex_t	forks[200];
	pthread_mutex_t	writing;
	pthread_mutex_t	eaten_meal;
}	t_rules;

int			init_struct(t_rules *rules, int ac, char **av);
long long	time_diff(long long cur, long long prev);
long long	get_time(void);
void		phi_sleep(long long time, t_philo *p);
void		*threads(void	*ph);
int			feastin(t_rules *r);
void		eat(t_philo *phils);
void		action_dis(t_rules *r, int id, char *s);
void		thread_exit(t_rules *r, t_philo *phil);
int			phil_init(t_rules *rules);
int			init_mutex(t_rules *r);
int			isnum(char **av);
int			phil_atoi(char *s);
void		death_check(t_rules *r, t_philo *p);
int			solo_phil(t_rules *r);

#endif