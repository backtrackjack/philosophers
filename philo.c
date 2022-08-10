/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:15:24 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/10 22:13:26 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/_pthread/_pthread_mutex_t.h>
#include <time.h>
#include "philo.h"

void *philosopher(void *);
void think(t_philo *);
void pickUp(t_philo *);
void eat(t_philo *);
void putDown(t_philo *);

pthread_mutex_t chopsticks[NUMBER_OF_PHILOSOPHERS];

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
		pthread_create(&data.threads[i], NULL, philosopher, &data.philos[i]);
		i++;
	}
	i = 0;
	while (i < data.philo_num) 
		pthread_join(data.threads[i++], NULL);
	return 0;
} 

