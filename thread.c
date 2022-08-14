/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:46:44 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/14 23:12:58 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <pthread.h>
#include <sys/_types/_timeval.h>
#include <sys/select.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

static void think(t_philo *p) {
	pthread_mutex_lock(p->data->lock);	
	if (check_death(p))
	{
		printf("%lu %d is thinking\n", get_timestamp(p->data), p->id);
		usleep(p->data->time_to_sleep * 1000);
	}
	pthread_mutex_unlock(p->data->lock);
}

static void ft_sleep(t_philo *p) {
	pthread_mutex_lock(p->data->lock);
	if (check_death(p))
	{
		printf("%lu %d is sleeping\n", get_timestamp(p->data), p->id);
		usleep(p->data->time_to_sleep * 1000);
	}
	pthread_mutex_unlock(p->data->lock);
}

static void pick_up(t_philo *p) {
	pthread_mutex_lock(p->data->lock);
	int right = (p->id + 1) % p->data->philo_num;
	int left = (p->id + p->data->philo_num) % p->data->philo_num;
	if (check_death(p))
	{
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
	}
	pthread_mutex_unlock(p->data->lock);
}

static void eat(t_philo *p) {
	pthread_mutex_lock(p->data->lock);
	if (check_death(p)) 
	{	
		printf("%lu %d is eating\n", get_timestamp(p->data), p->id);
		usleep(p->data->time_to_eat * 1000);
		p->last_meal = get_timestamp(p->data);
		p->times_eaten++;
		if (p->times_eaten == p->data->number_of_times_philo_must_eat)
			p->data->full++;
		pthread_mutex_unlock(&p->data->forks[(p->id + 1) % p->data->philo_num]);
		pthread_mutex_unlock(&p->data->forks[(p->id + p->data->philo_num)
				% p->data->philo_num]);
	}
	pthread_mutex_unlock(p->data->lock);
}

void *philosopher(void *philo) {
	t_philo *p;
	int		dead;
	int		full;
	p = (t_philo *)philo;	
	dead = 0;
	full = 0;
	while (1) {
		think(p);
		pick_up(p);
		eat(p);
		ft_sleep(p);
		full = p->data->full;
		dead = p->data->dead;
		if (dead || full == p->data->philo_num)
			break;
	}
	return (NULL);
}

