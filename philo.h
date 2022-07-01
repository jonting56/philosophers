/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:42:55 by jting             #+#    #+#             */
/*   Updated: 2022/07/01 10:49:05 by jting            ###   ########.fr       */
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
	t_philo			philos[250];
	pthread_mutex_t	forks[250];
}	t_rules;

typedef struct s_philo
{
	int				left_fork;
	int				right_fork;
	int				each_eat;
	long			eat_time;
	pthread_t		thread_id;
	pthread_mutex_t	*m;
	int				id;
	t_rules			*rules;
}	t_philo;

int		init_struct(t_rules *data, int ac, char **av);
long	get_time(void);
void	*looping(t_rules data);
void	eat(t_rules *data, int phil);

#endif