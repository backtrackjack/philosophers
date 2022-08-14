/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:46:44 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/14 18:29:37 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void think(t_philo *p) {
	int sleepTime = p->data->time_to_sleep;
	printf("p %d will think for %d seconds\n", p->id, sleepTime);
	sleep(sleepTime);
}

static void pick_up(t_philo *p) {
	int right = (p->id + 1) % p->data->philo_num;
	int left = (p->id + p->data->philo_num) % p->data->philo_num;
	if (p->id & 1) {
		pthread_mutex_lock(&p->data->forks[right]);
		printf("p %d picked up fork %d\n", p->id, right);
		pthread_mutex_lock(&p->data->forks[left]);
		printf("p %d picked up fork %d\n", p->id, left);
	}
	else {
		pthread_mutex_lock(&p->data->forks[left]);
		printf("p %d picked up fork %d\n", p->id, left);
		pthread_mutex_lock(&p->data->forks[right]);
		printf("p %d picked up fork %d\n", p->id, right);
	}
}

static void eat(t_philo *p) {
	int eatTime = p->data->time_to_eat;
	printf("p %d will eat for %d seconds\n", p->id, eatTime);
	sleep(eatTime);
}

static void put_down(t_philo *p) {
	pthread_mutex_unlock(&p->data->forks[(p->id + 1) % p->data->philo_num]);
	pthread_mutex_unlock(&p->data->forks[(p->id + p->data->philo_num)
			% p->data->philo_num]);
}

void *philosopher(void *p) {
	while (1) {
		think((t_philo *)p);
		pick_up((t_philo *)p);
		eat((t_philo *)p);
		put_down((t_philo *)p);
	}
}

