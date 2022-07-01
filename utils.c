/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jting <jting@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 12:48:48 by jting             #+#    #+#             */
/*   Updated: 2022/07/01 11:58:29 by jting            ###   ########.fr       */
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
// Returns the amount of time since the launch of the program
long long	get_time(void)
{
	struct timeval			current;

	gettimeofday(&current, NULL);
	return ((current.tv_sec * 1000) + (current.tv_usec / 1000));
}

long long	time_diff(long long prev, long long cur)
{
	return (cur - prev);
}