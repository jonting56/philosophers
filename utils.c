/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:48:48 by jting             #+#    #+#             */
/*   Updated: 2022/06/24 16:34:20 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static long	phil_atoi(char *s)
{
	long	result;
	int		i;

	i = 0;
	result = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] >= '0' && s[i] < '9' && s[i])
	{
		result *= 10;
		result += result + s[i] - '0';
		i++;
	}
	return (result);
}

static	int	isnum(int ac, char **av)
{
	int	i;
	int	j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] > '9' && av[i][j] < '0')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

long	get_time(void)
{
	struct timeval			current;
	static struct timeval	*initial = NULL;

	if (!initial)
	{
		initial = malloc(sizeof(initial));
		gettimeofday(initial, NULL);
	}
	else
	{
		gettimeofday(&current, NULL);
		return (((current.tv_sec) * 1000 + (current.tv_usec) / 1000)
			- ((initial->tv_sec) * 1000 + (initial->tv_usec) / 1000));
	}
	return (0);
}

int	init_struct(t_thread *data, int ac, char **av)
{
	int	i;

	i = -1;
	if ((ac < 5 || ac > 6) || !isnum(ac, av))
		return (0);
	data = malloc(sizeof(t_thread));
	data->philo_num = phil_atoi(1);
	data->time_to_die = phil_atoi(2);
	data->time_to_eat = phil_atoi(3);
	data->time_to_sleep = phil_atoi(4);
	data->is_alive = 1;
	if (ac == 5)
		data->times_eaten = phil_atoi(5);
	else
		data->times_eaten = -1;
	while (++i < philo_atoi(av[1]))
	{
		pthread_create(*data->philos.thread_id[i], NULL, looping, &data->philos[i]);
		data->philos[i].fork = 1;
		pthread_mutex_init(&data->philos[i].forks, NULL);
	}
	return (1);
}

int init_philo(t_thread *data, int ac, char **av)