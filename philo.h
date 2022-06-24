/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:42:55 by jting             #+#    #+#             */
/*   Updated: 2022/06/24 16:48:12 by jting            ###   ########.fr       */
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

typedef struct s_thread
{
	int		philo_num;
	long	time_to_die;
	long	time_to_eat;
	long	time_to_sleep;
	int		times_eaten;	
	int		is_alive;
	t_philo	*philos;
}	t_thread;

typedef struct s_philo
{
	int				fork;
	int				each_eat;
	pthread_t		thread_id;
	pthread_mutex_t	*mutex;
	int				id;
}	t_philo;

int		init_struct(t_thread *data, int ac, char **av);
long	get_time(void);
void	looping(t_thread data);

#endif