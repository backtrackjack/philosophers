/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:15:24 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/10 18:56:33 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include "philo.h"

void *philosopher(void *);
void think(int);
void pickUp(int);
void eat(int);
void putDown(int);

pthread_mutex_t chopsticks[NUMBER_OF_PHILOSOPHERS];

void	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(data->philo_num* sizeof(t_philo));
	while (i < data->philo_num)
	{
		data->philos[i].id = i + 1;
		data->philos[i].times_eaten = 0;
		i++;
	}
}

void	ft_init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->philo_num = 5;
	data->time_to_die = 10;
	data->time_to_eat = 10; 
	data->time_to_sleep = 10;
	if (1)
		data->number_of_times_philo_must_eat = 7;
	else
		data->number_of_times_philo_must_eat = -1;
	ft_init_philos(data);
}

int main() {
	int i;

	srand(time(NULL));
	t_data data;
	ft_init_data(&data);
	i = -1;
	while (i < data.philo_num) 
		pthread_mutex_init(&data.forks[++i], NULL);
	i = 0;	
	while (i < data.philo_num) {
		pthread_create(&data.philosophers[i], NULL, philosopher, &data.philos[i]);
		i++;
	}
	i = -1;
	while (i < data.philo_num) {
		pthread_join(data.philosophers[++i], NULL);
	}
	return 0;
}

void *philosopher(void *philosopher) {
	while (1) {
		think(*(int *)philosopher);
		pickUp(*(int *)philosopher);
		eat(*(int *)philosopher);
		putDown(*(int *)philosopher);
	}
}

void think(int philosopherNumber) {
	int sleepTime = 1;
	printf("Philosopher %d will think for %d seconds\n", philosopherNumber, sleepTime);
	sleep(sleepTime);
}

void pickUp(int philosopherNumber) {
	int right = (philosopherNumber + 1) % NUMBER_OF_PHILOSOPHERS;
	int left = (philosopherNumber + NUMBER_OF_PHILOSOPHERS) % NUMBER_OF_PHILOSOPHERS;
	if (philosopherNumber & 1) {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
	}
	else {
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, left);
		pthread_mutex_lock(&chopsticks[left]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, left);
		printf("Philosopher %d is waiting to pick up chopstick %d\n", philosopherNumber, right);
		pthread_mutex_lock(&chopsticks[right]);
		printf("Philosopher %d picked up chopstick %d\n", philosopherNumber, right);
	}
}

void eat(int philosopherNumber) {
	int eatTime = rand() % 3 + 1;
	printf("Philosopher %d will eat for %d seconds\n", philosopherNumber, eatTime);
	sleep(eatTime);
}

void putDown(int philosopherNumber) {
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + 1) % NUMBER_OF_PHILOSOPHERS]);
	pthread_mutex_unlock(&chopsticks[(philosopherNumber + NUMBER_OF_PHILOSOPHERS) % NUMBER_OF_PHILOSOPHERS]);
}
