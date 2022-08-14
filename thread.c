/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:46:44 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/14 20:48:02 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/_types/_timeval.h>
#include <sys/select.h>
#include <sys/time.h>

long	get_timestamp(t_data *d)
{
	gettimeofday(d->current_time, NULL);	
	return (d->current_time->tv_sec * 1000
			+ d->current_time->tv_usec / 1000);
}

static void think(t_philo *p) {
	pthread_mutex_lock(p->data->lock);
	printf("%lu %d is thinking\n", get_timestamp(p->data), p->id);
	usleep(p->data->time_to_sleep * 1000);
	pthread_mutex_unlock(p->data->lock);
}

static void ft_sleep(t_philo *p) {
	pthread_mutex_lock(p->data->lock);
	printf("%lu %d is sleeping\n", get_timestamp(p->data), p->id);
	usleep(p->data->time_to_sleep * 1000);
	pthread_mutex_unlock(p->data->lock);
}

static void pick_up(t_philo *p) {
	pthread_mutex_lock(p->data->lock);
	int right = (p->id + 1) % p->data->philo_num;
	int left = (p->id + p->data->philo_num) % p->data->philo_num;
	if (p->id & 1) {
		pthread_mutex_lock(&p->data->forks[right]);
		printf("%lu %d has taken a fork\n", get_timestamp(p->data), p->id);
		pthread_mutex_lock(&p->data->forks[left]);
		printf("%lu %d has taken a fork\n", get_timestamp(p->data), p->id);
	}
	else {
		pthread_mutex_lock(&p->data->forks[left]);
		printf("%lu %d has taken a fork\n", get_timestamp(p->data), p->id);
		pthread_mutex_lock(&p->data->forks[right]);
		printf("%lu %d has taken a fork\n", get_timestamp(p->data), p->id);
	}
	pthread_mutex_unlock(p->data->lock);
}

static void eat(t_philo *p) {
	pthread_mutex_lock(p->data->lock);
	printf("%lu %d is eating\n", get_timestamp(p->data), p->id);
	usleep(p->data->time_to_eat * 1000);
	p->last_meal = get_timestamp(p->data);
	p->times_eaten++;
	pthread_mutex_unlock(&p->data->forks[(p->id + 1) % p->data->philo_num]);
	pthread_mutex_unlock(&p->data->forks[(p->id + p->data->philo_num)
			% p->data->philo_num]);
	pthread_mutex_unlock(p->data->lock);
}

void *philosopher(void *p) {
	while (1) {
		think((t_philo *)p);
		pick_up((t_philo *)p);
		eat((t_philo *)p);
		ft_sleep((t_philo *)p);
	}
}

