/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 21:43:14 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/14 18:26:25 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_init_philos(t_data *data)
{
	int	i;

	i = 0;
	data->philos = (t_philo *)malloc(data->philo_num * sizeof(t_philo));
	while (i < data->philo_num)
	{
		data->philos[i].id = i;
		data->philos[i].times_eaten = 0;
		data->philos[i].data = data;
		i++;
	}
}

void	ft_init_data(t_data *data)
{
	memset(data, 0, sizeof(t_data));
	data->philo_num = 5;
	data->time_to_die = 10;
	data->time_to_eat = 1; 
	data->time_to_sleep = 3;
	data->forks = malloc(data->philo_num * sizeof(pthread_mutex_t));
	data->threads = malloc(data->philo_num * sizeof(pthread_t)); 
	data->lock = malloc(sizeof(pthread_mutex_t));
	if (1)
		data->number_of_times_philo_must_eat = 7;
	else
		data->number_of_times_philo_must_eat = -1;
	ft_init_philos(data);
}
