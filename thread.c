/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:46:44 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/10 21:47:48 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void think(t_philo *philosopher) {
	int sleepTime = philosopher->data->time_to_sleep;
	printf("Philosopher %d will think for %d seconds\n", philosopher->id, sleepTime);
	sleep(sleepTime);
}

static void pickUp(t_philo *philosopher) {
	int right = (philosopher->id + 1) % philosopher->data->philo_num;
	int left = (philosopher->id + philosopher->data->philo_num) % philosopher->data->philo_num;
	if (philosopher->id & 1) {
		pthread_mutex_lock(&philosopher->data->forks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopher->id, right);
		pthread_mutex_lock(&philosopher->data->forks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopher->id, left);
	}
	else {
		pthread_mutex_lock(&philosopher->data->forks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopher->id, left);
		pthread_mutex_lock(&philosopher->data->forks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopher->id, right);
	}
}

static void eat(t_philo *philosopher) {
	int eatTime = philosopher->data->time_to_eat;
	printf("Philosopher %d will eat for %d seconds\n", philosopher->id, eatTime);
	sleep(eatTime);
}

static void putDown(t_philo *philosopher) {
	pthread_mutex_unlock(&philosopher->data->forks[(philosopher->id + 1) % philosopher->data->philo_num]);
	pthread_mutex_unlock(&philosopher->data->forks[(philosopher->id + philosopher->data->philo_num) % philosopher->data->philo_num]);
}

void *philosopher(void *philosopher) {
	while (1) {
		think((t_philo *)philosopher);
		pickUp((t_philo *)philosopher);
		eat((t_philo *)philosopher);
		putDown((t_philo *)philosopher);
	}
}

