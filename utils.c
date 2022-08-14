/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/14 21:19:24 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/14 21:50:09 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	get_timestamp(t_data *d)
{
	gettimeofday(d->current_time, NULL);	
	return (d->current_time->tv_sec * 1000
			+ d->current_time->tv_usec / 1000);
}

int	check_death(t_philo *p)
{
	if (get_timestamp(p->data) - p->last_meal >= p->data->time_to_die)
	{
		p->data->dead = 1;
		printf("%lu %d died\n", get_timestamp(p->data), p->id);
		return (0);
	}
	else
		return (1);
}
