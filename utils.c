/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:48:48 by jting             #+#    #+#             */
/*   Updated: 2022/07/07 16:16:41 by jting            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	phil_atoi(char *s)
{
	int	result;
	int	i;

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

// Returns the time at point use

long long	get_time(void)
{
	struct timeval			current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

// Returns time diff

long long	time_diff(long long prev, long long cur)
{
	return (cur - prev);
}

void	phi_sleep(long long time, t_rules *r)
{
	long long	i;

	i = get_time();
	while (!(r->is_alive))
	{
		if (time_diff(i, get_time()) >= time)
			break ;
		usleep(50);
	}
}

int	isnum(char **av)
{
	int		i;
	int		j;

	i = 1;
	while (av[i])
	{
		j = 0;
		while (av[i][j])
		{
			if (av[i][j] <= '9' && av[i][j] >= '0')
				j++;
			else
				return (0);
		}
		i++;
	}
	return (1);
}
