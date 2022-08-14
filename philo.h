/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsellars <jsellars@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 15:31:06 by jsellars          #+#    #+#             */
/*   Updated: 2022/08/14 21:42:38 by jsellars         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
#include <sys/_types/_timeval.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <stdio.h>
# include <string.h>

typedef struct s_philo
{
	int				id;	
	int				times_eaten;	
	long			last_meal;
	struct s_data	*data;
}			t_philo;

typedef struct s_data
{
	t_philo			*philos;
	int				philo_num;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_philo_must_eat; 
	int				dead;
	int				full;
	struct timeval	*current_time;
	pthread_mutex_t	*forks;
	pthread_t		*threads;
	pthread_mutex_t *lock;
}			t_data;

void	ft_init_philos(t_data *data);
void	ft_init_data(t_data *data);	
long	get_timestamp(t_data *d);
int		check_death(t_philo *p);
#endif
